// AllocationSetupTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <sstream>

#define NOMINMAX 1
#include <Windows.h>

#pragma warning(push)
#pragma warning(disable : 4100 4458)
#include <lyra/lyra.hpp>
#pragma warning(pop)

#include "ResultSet.h"
#include "DbgHelpUtils/handles.h"
#include "DbgHelpUtils/join.h"
#include "DbgHelpUtils/string_conversation.h"

using namespace std::string_literals;
using namespace std::string_view_literals;

int LfhAllocations(std::wostream& log, std::wstring const& dump_filename, std::function<void*(size_t size)> const& allocator, std::function<void(void*)> const& deallocator, ResultSet& set);
int VirtualAllocations(std::wostream& log, std::wstring const& dump_filename, std::function<void*(size_t size)> const& allocator, std::function<void(void*)> const& deallocator, ResultSet& set);
int AllocateSizeRanges(std::wostream& log, std::wstring const& dump_filename, std::function<void*(size_t size)> const& allocator, std::function<void(void*)> const& deallocator, ResultSet& set);
template<size_t N>
bool AllocateBuffers(std::wostream& log, std::function<void*(size_t size)> const& allocator, std::array<void*, N>& allocations, char& fill_value, size_t allocation_size, size_t increase_amount, char const* type, ResultSet& set);
template<size_t N>
void DeallocateSomeBuffers(std::wostream& log, ResultSet& set, std::function<void(void*)> const& deallocator, std::array<void*, N>& allocations);

template<size_t N, typename ...Args>
void DeallocateSomeBuffers(std::wostream& log, ResultSet& set, std::function<void(void*)> const& deallocator, std::array<void*, N>& allocations, Args... args)
{
    DeallocateSomeBuffers(log, set, deallocator, allocations);
    DeallocateSomeBuffers(log, set, deallocator, args...);
}

void DeallocateSomeBuffer(std::wostream& log, ResultSet& set, std::function<void(void*)> const& deallocator, void* allocation);

void FreeAllocationInResultSet(ResultSet& set, void* allocation);

void CreateOutput(std::wostream& log, std::wstring const& dump_filename);
void GenerateDumpFile(std::wostream& log, std::wstring const& dump_filename);

int main(int const argc, char* argv[])
{
    try
    {
        try
        {
            using allocator_type = std::function<void*(size_t)>;
            using deallocator_type = std::function<void(void*)>;
            using allocation_functions_data = std::pair<allocator_type, deallocator_type>;
            std::map<std::string, allocation_functions_data> const allocation_functions
            {
                { "heapalloc"s, {[](size_t const size) { return HeapAlloc(GetProcessHeap(), 0x0, size); }, [](void* memory) { HeapFree(GetProcessHeap(), 0x0, memory); }}},
                { "malloc"s, {[](size_t const size) { return malloc(size); }, [](void* memory) { free(memory); }}},
                { "new"s, {[](size_t const size) { return new char[size]; }, [](void* memory) { delete[] static_cast<char*>(memory); }}}
            };

            using test_type = std::function<int(std::wostream&, std::wstring const&, std::function<void*(size_t)> const&, std::function<void(void*)> const&, ResultSet&)>;
            std::map<std::string, test_type> const test_functions
            {
                { "lfh"s, LfhAllocations},
                { "virtual"s, VirtualAllocations},
                { "sizes"s, AllocateSizeRanges}
            };

            std::string dump_filename_l;
            std::string log_filename_l;
            std::string json_filename_l;
            std::string allocation_test;
            std::string allocation_type;
            auto show_help{false};

            auto cli = lyra::help(show_help)
                | lyra::opt(allocation_test, dlg_help_utils::join(test_functions | std::views::keys, "|"sv))["--test"]("generate test of allocations").choices([&test_functions](std::string const& value) { return test_functions.find(value) != test_functions.end(); })
                | lyra::opt(allocation_type, dlg_help_utils::join(allocation_functions | std::views::keys, "|"sv))["--type"]("application type").choices([&allocation_functions](std::string const& value) { return allocation_functions.find(value) != allocation_functions.end(); })
                | lyra::opt( dump_filename_l, "filename" )["-d"]["--dmp"]("dump filename")
                | lyra::opt( log_filename_l, "filename" )["-l"]["--log"]("log filename")
                | lyra::opt( json_filename_l, "filename" )["-j"]["--json"]("json filename")
                ;

            if (auto const result = cli.parse({ argc, argv });
                !result)
            {
                std::cerr << "Error in command line: " << result.errorMessage() << '\n';
                std::cerr << cli << "\n";
                return EXIT_FAILURE;
            }

            // Show the help when asked for.
            if (show_help)
            {
                std::cout << cli << '\n';
                return EXIT_SUCCESS;
            }

            if (allocation_test.empty())
            {
                std::cerr << "No allocation test specified\n";
                std::cout << cli << '\n';
                return EXIT_SUCCESS;
            }

            if (allocation_type.empty())
            {
                std::cerr << "No allocation type specified\n";
                std::cout << cli << '\n';
                return EXIT_SUCCESS;
            }

            using dlg_help_utils::string_conversation::acp_to_wstring;
            auto const dump_filename = acp_to_wstring(dump_filename_l);
            auto const log_filename = acp_to_wstring(log_filename_l);
            auto const json_filename = acp_to_wstring(json_filename_l);

            auto const& allocation_function_data = allocation_functions.at(allocation_type);
            auto const& allocator = std::get<0>(allocation_function_data);
            auto const& deallocator = std::get<1>(allocation_function_data);

            std::unique_ptr<std::wfstream> log;
            std::wostream* o_log{&std::wcout};
            if(!log_filename.empty())
            {
                log = std::make_unique<std::wfstream>(log_filename, std::ios_base::out | std::ios_base::trunc);
                if(log->bad())
                {
                    std::wcout << "failed to open log file: " << log_filename << '\n';
                    return EXIT_FAILURE;
                }
                o_log = log.get();
            }

            ResultSet set;
            auto result = test_functions.at(allocation_test)(*o_log, dump_filename, allocator, deallocator, set);

            if(!json_filename.empty())
            {
                std::fstream json_file{json_filename, std::ios_base::out | std::ios_base::trunc};
                if(json_file.bad())
                {
                    std::wcout << "failed to open json result set file: " << json_filename << '\n';
                    return EXIT_FAILURE;
                }
                json_file << JS::serializeStruct(set);
                json_file.close();
            }

            log->close();
            return result;
        }
        catch (std::exception const& e)
        {
            std::cout << "fatal error: " << e.what() << '\n';
        }
        catch (...)
        {
            std::cout << "fatal error: Unknown exception\n";
        }
    }
    catch(...)
    {
    }
    return EXIT_FAILURE;
}

int LfhAllocations(std::wostream& log, std::wstring const& dump_filename, std::function<void*(size_t size)> const& allocator, std::function<void(void*)> const& deallocator, ResultSet& set)
{
    std::array<void*, 0x12> backend_allocations{};
    constexpr size_t allocation_size = 0x10;

    char fill_value = 'A';
    if (!AllocateBuffers(log, allocator, backend_allocations, fill_value, allocation_size, 0, "backend", set))
    {
        return EXIT_FAILURE;
    }

    std::array<void*, 0x12> frontend_allocations{};
    if (!AllocateBuffers(log, allocator, frontend_allocations, fill_value, allocation_size, 0, "frontend", set))
    {
        return EXIT_FAILURE;
    }

    DeallocateSomeBuffers(log, set, deallocator, backend_allocations, frontend_allocations);

    CreateOutput(log, dump_filename);

    return EXIT_SUCCESS;
}


int VirtualAllocations(std::wostream& log, std::wstring const& dump_filename, std::function<void*(size_t size)> const& allocator, std::function<void(void*)> const& deallocator, ResultSet& set)
{
    std::array<void*, 0x5> virtual_allocations{};
    
    if (char fill_value = 'A';
        !AllocateBuffers(log, allocator, virtual_allocations, fill_value, 0x100000, 0, "virtual", set))
    {
        return EXIT_FAILURE;
    }

    DeallocateSomeBuffers(log, set, deallocator, virtual_allocations);

    CreateOutput(log, dump_filename);

    return EXIT_SUCCESS;
}

int AllocateSizeRanges(std::wostream& log, std::wstring const& dump_filename, std::function<void*(size_t size)> const& allocator, std::function<void(void*)> const& deallocator, ResultSet& set)
{
    size_t allocation_size = 0x1;

    auto constexpr max_rounds = 6;

    std::array<std::array<void*, 0xF>, max_rounds> allocation_groups{};
    std::array<std::array<void*, 0xE>, max_rounds - 1> small_allocation_groups{};

    for(auto index = 0; index < max_rounds; ++index)
    {
        char fill_value = 'A';
        if (!AllocateBuffers(log, allocator, allocation_groups[index], fill_value, allocation_size, allocation_size, "sizes", set))
        {
            return EXIT_FAILURE;
        }
        if(allocation_size > 1)
        {
            if (!AllocateBuffers(log, allocator, small_allocation_groups[index - 1], fill_value, allocation_size + 1, 1, "sizes", set))
            {
                return EXIT_FAILURE;
            }
        }
        allocation_size *= 0x10;
    }

    for(auto& allocations : allocation_groups)
    {
        DeallocateSomeBuffers(log, set, deallocator, allocations);
    }

    for(auto& allocations : small_allocation_groups)
    {
        DeallocateSomeBuffers(log, set, deallocator, allocations);
    }

    CreateOutput(log, dump_filename);
    return EXIT_SUCCESS;
}

template<size_t N>
bool AllocateBuffers(std::wostream& log, std::function<void*(size_t size)> const& allocator, std::array<void*, N>& small_allocations, char& fill_value, size_t allocation_size, size_t const increase_amount, char const* type, ResultSet& set)
{
    for (auto& virtual_allocation : small_allocations)
    {
        virtual_allocation = allocator(allocation_size);
        log << type << " allocation [0x" << virtual_allocation <<  " / " << reinterpret_cast<uint64_t>(virtual_allocation) << "] fill value [" << fill_value << "]  buffer size [0x" << std::hex << allocation_size << std::dec << " | " << allocation_size << "]\n";
        if(virtual_allocation == nullptr)
        {
            log << "Failed to allocate " << type << " allocation\n";
            return false;
        }
        memset(virtual_allocation, fill_value, allocation_size);

        set.allocations.emplace_back(Allocation{reinterpret_cast<uint64_t>(virtual_allocation), allocation_size, fill_value, true});

        ++fill_value;
        allocation_size += increase_amount;
    }
    return true;
}

template<size_t N>
void DeallocateSomeBuffers(std::wostream& log, ResultSet& set, std::function<void(void*)> const& deallocator, std::array<void*, N>& allocations)
{
    DeallocateSomeBuffer(log, set, deallocator, allocations[1]);
    DeallocateSomeBuffer(log, set, deallocator, allocations[3]);
}

void DeallocateSomeBuffer(std::wostream& log, ResultSet& set, std::function<void(void*)> const& deallocator, void* allocation)
{
    deallocator(allocation);
    log << "deallocate [0x" << allocation <<  " / " << reinterpret_cast<uint64_t>(allocation) << "]\n";
    FreeAllocationInResultSet(set, allocation);
}

void FreeAllocationInResultSet(ResultSet& set, void* allocation)
{
    if(auto const it = std::ranges::find_if(set.allocations, [allocation](Allocation const& a) { return a.allocated && a.pointer == reinterpret_cast<uint64_t>(allocation); });
        it != set.allocations.end())
    {
        it->allocated = false;
    }
}

void CreateOutput(std::wostream& log, std::wstring const& free_dump_filename)
{
    if(free_dump_filename.empty())
    {
        std::cout << "press enter to exit\n";
        [[maybe_unused]] auto const ch2 = getchar();
    }
    else
    {
        GenerateDumpFile(log, free_dump_filename);
    }
}

void GenerateDumpFile(std::wostream& log, std::wstring const& dump_filename)
{
    std::wostringstream ss;

    // ReSharper disable once StringLiteralTypo
    ss << "procdump -ma " << GetCurrentProcessId() << " \"" << dump_filename << "\"";
    auto const command = std::move(ss).str();


    SECURITY_ATTRIBUTES security_attributes;

    // Set the bInheritHandle flag so pipe handles are inherited. 
    security_attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    security_attributes.bInheritHandle = TRUE;
    security_attributes.lpSecurityDescriptor = nullptr;

    // Create a pipe for the child process's STDOUT.
    HANDLE out_write_pipe_handle{nullptr};
    HANDLE out_read_pipe_handle{nullptr};
    if (!CreatePipe(&out_read_pipe_handle, &out_write_pipe_handle, &security_attributes, 0))
    {
        log << "Failed to create pipe : 0x" << std::hex << GetLastError() << std::dec << '\n';
        return;
    }

    using dlg_help_utils::handles::make_handle;
    auto const out_write_handle = make_handle(out_write_pipe_handle, CloseHandle);
    auto const out_read_handle = make_handle(out_read_pipe_handle, CloseHandle);

    STARTUPINFOW startup_info;
    PROCESS_INFORMATION process_info;
    memset(&startup_info, 0, sizeof(startup_info));
    memset(&process_info, 0, sizeof(process_info));
    startup_info.cb = sizeof(startup_info);
    startup_info.hStdError = out_write_pipe_handle;
    startup_info.hStdOutput = out_write_pipe_handle;
    startup_info.hStdInput = out_read_pipe_handle;
    startup_info.dwFlags |= STARTF_USESTDHANDLES;

    if(command.size() >= MAX_PATH)
    {
        log << "Command line [" << command << "] to long : " << command.size() << " >= " << MAX_PATH << '\n';
        return;
    }

    wchar_t temp[MAX_PATH];
    wcsncpy_s(temp, command.c_str(), command.size());
    temp[command.size()] = 0;

    if (!CreateProcessW(nullptr, temp, nullptr, nullptr, false, 0, nullptr, nullptr, &startup_info, &process_info))
    {
        log << "CreateProcessW [" << command << "] failed : 0x" << std::hex << GetLastError() << std::dec << '\n';
        return;
    }

    //Close thread handle. 
    CloseHandle(process_info.hThread);

    // Wait for dump to complete...
    WaitForSingleObject(process_info.hProcess, INFINITE);

    // Close process handle.
    CloseHandle(process_info.hProcess);

    log << "Dump file created: " << dump_filename << '\n';
}
