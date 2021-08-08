﻿#include "stream_utils.h"

#include <sstream>

#include "mini_dump.h"
#include "nt_heap.h"
#include "string_compare.h"
#include "symbol_type_info.h"
#include "sym_tag_enum.h"
#include "wide_runtime_error.h"

namespace dlg_help_utils::stream_utils
{
    std::optional<std::tuple<size_t, MINIDUMP_DIRECTORY const&>> find_stream_for_type(mini_dump const& dump_file, MINIDUMP_STREAM_TYPE const type)
    {
        auto const* header = dump_file.header();
        if (header == nullptr)
        {
            return std::nullopt;
        }

        auto const* directory = dump_file.directory();
        if (directory == nullptr)
        {
            return std::nullopt;
        }

        for (size_t index = 0; index < header->NumberOfStreams; ++index)
        {
            if (auto const & entry = directory[index]; static_cast<MINIDUMP_STREAM_TYPE>(entry.StreamType) == type)
            {
                return std::make_tuple(index, entry);
            }
        }

        return std::nullopt;
    }

    std::optional<std::pair<dbg_help::symbol_type_info, uint64_t>> find_field_in_type(dbg_help::symbol_type_info type, std::wstring_view field_name)
    {
        uint64_t offset{0};
        while(true)
        {
            auto const pos = field_name.find_first_of(L'.');
            auto const find_name_part = pos == std::wstring_view::npos ? field_name : field_name.substr(0, pos);
            auto const find_name_rest = pos == std::wstring_view::npos ? std::wstring_view{} : field_name.substr(pos + 1);
            if(auto const type_tag_data = type.sym_tag(); type_tag_data.value_or(dbg_help::sym_tag_enum::Null) != dbg_help::sym_tag_enum::UDT)
            {
                return std::nullopt;
            }

            auto found = false;
            for (auto const& child : type.children())
            {
                if(auto const name_data = child.name(); name_data.has_value() && string_compare::iequals(find_name_part, name_data.value()))
                {
                    if(find_name_rest.empty())
                    {
                        return std::make_pair(child, offset);
                    }

                    if(auto const child_type = child.type(); child_type.has_value())
                    {
                        if(auto const child_offset = child.offset(); child_offset.has_value())
                        {
                            found = true;
                            field_name = find_name_rest;
                            type = child_type.value();
                            offset += child_offset.value();
                            break;
                        }
                    }
                }
            }

            if(!found)
            {
                return std::nullopt;
            }
        }
    }

    std::optional<std::pair<dbg_help::symbol_type_info, uint64_t>> get_field_pointer_type_and_value(stream_stack_dump::mini_dump_stack_walk const& walker, dbg_help::symbol_type_info const& pointer_type, uint64_t memory_address, size_t const index)
    {
        if(auto const type_tag_data = pointer_type.sym_tag(); type_tag_data.value_or(dbg_help::sym_tag_enum::Null) != dbg_help::sym_tag_enum::PointerType)
        {
            return std::nullopt;
        }

        auto const data_type_length = pointer_type.length();
        if(!data_type_length.has_value())
        {
            return std::nullopt;
        }

        auto const data_type = pointer_type.type();
        if(!data_type.has_value())
        {
            return std::nullopt;
        }

        memory_address += (index * data_type_length.value());

        std::optional<uint64_t> value;
        switch(data_type_length.value())
        {
        case 4:
            value = read_field_value<uint32_t, uint64_t>(walker, memory_address);
            break;

        case 8:
            value = read_field_value<uint64_t, uint64_t>(walker, memory_address);
            break;

        default:
            return std::nullopt;
        }

        if(!value.has_value())
        {
            return std::nullopt;
        }

        return std::make_pair(data_type.value(), value.value());
    }

    std::optional<std::pair<dbg_help::symbol_type_info, uint64_t>> find_field_type_and_offset_in_type(dbg_help::symbol_type_info const& type, std::wstring_view const field_name, dbg_help::sym_tag_enum const tag)
    {
        auto const field_data = find_field_in_type(type, field_name);
        if(!field_data.has_value())
        {
            return std::nullopt;
        }

        auto const [field, base_offset] = field_data.value();

        auto const data_type = field.type(); 
        if(!data_type.has_value())
        {
            return std::nullopt;
        }

        if(auto const data_type_tag = data_type.value().sym_tag(); data_type_tag.value_or(dbg_help::sym_tag_enum::Null) != tag)
        {
            return std::nullopt;
        }

        auto const offset_data = field.offset();
        if(!offset_data.has_value())
        {
            return std::nullopt;
        }

        return std::make_pair(data_type.value(), offset_data.value() + base_offset);
    }

    std::optional<std::pair<dbg_help::symbol_type_info, uint64_t>> find_field_pointer_type_and_value_in_type(stream_stack_dump::mini_dump_stack_walk const& walker, dbg_help::symbol_type_info const& type, std::wstring_view const field_name, uint64_t const memory_address)
    {
        auto const type_and_offset = find_field_type_and_offset_in_type(type, field_name, dbg_help::sym_tag_enum::PointerType);
        if(!type_and_offset.has_value())
        {
            return std::nullopt;
        }

        auto const& [data_type, offset] = type_and_offset.value();

        auto const data_type_length = data_type.length();
        if(!data_type_length.has_value())
        {
            return std::nullopt;
        }

        std::optional<uint64_t> value;
        switch(data_type_length.value())
        {
        case 4:
            value = read_field_value<uint32_t, uint64_t>(walker, memory_address + offset);
            break;

        case 8:
            value = read_field_value<uint64_t, uint64_t>(walker, memory_address + offset);
            break;

        default:
            return std::nullopt;
        }

        if(!value.has_value())
        {
            return std::nullopt;
        }

        return std::make_pair(data_type, value.value());
    }

    std::optional<uint64_t> find_field_pointer_value_in_type(stream_stack_dump::mini_dump_stack_walk const& walker, dbg_help::symbol_type_info const& type, std::wstring_view const field_name, uint64_t const memory_address)
    {
        auto const value = find_field_pointer_type_and_value_in_type(walker, type, field_name, memory_address);
        if(!value.has_value())
        {
            return std::nullopt;
        }

        return std::get<1>(value.value());
    }

    std::optional<uint64_t> find_basic_type_field_address_in_type(dbg_help::symbol_type_info const& type, std::wstring_view const field_name, uint64_t const memory_address, size_t const field_size)
    {
        auto const type_and_offset = find_field_type_and_offset_in_type(type, field_name, dbg_help::sym_tag_enum::BaseType);
        if(!type_and_offset.has_value())
        {
            return std::nullopt;
        }

        auto const& [data_type, offset] = type_and_offset.value();

        auto const data_type_length = data_type.length();
        if(!data_type_length.has_value())
        {
            return std::nullopt;
        }

        if(data_type_length.value() == field_size)
        {
            return memory_address + offset;
        }

        return std::nullopt;
    }

    std::optional<std::tuple<std::unique_ptr<char[]>, uint64_t, uint64_t>> read_udt_value_in_type(stream_stack_dump::mini_dump_stack_walk const& walker, dbg_help::symbol_type_info const& type, std::wstring_view const field_name, uint64_t const memory_address)
    {
        auto const type_and_offset = find_field_type_and_offset_in_type(type, field_name, dbg_help::sym_tag_enum::UDT);
        if(!type_and_offset.has_value())
        {
            return std::nullopt;
        }

        auto const& [data_type, offset] = type_and_offset.value();

        auto const data_type_length = data_type.length();
        if(!data_type_length.has_value())
        {
            return std::nullopt;
        }

        if(data_type_length.value() == 0)
        {
            return std::nullopt;
        }

        auto buffer = std::make_unique<char[]>(data_type_length.value());
        auto const *value = walker.get_process_memory(memory_address + offset, data_type_length.value());

        if(value == nullptr)
        {
            return std::nullopt;
        }

        memcpy(buffer.get(), value, data_type_length.value());
        return std::make_tuple(std::move(buffer), data_type_length.value(), memory_address + offset);
    }

    uint32_t machine_field_size(heap::nt_heap const& heap)
    {
        if(heap.is_x86_target())
        {
            return sizeof(uint32_t);
        }

        if(heap.is_x64_target())
        {
            return sizeof(uint64_t);
        }

        return 0;
    }

    std::optional<uint64_t> read_machine_size_field_value(heap::nt_heap const& heap, uint64_t const memory_address)
    {
        if(heap.is_x86_target())
        {
            return read_field_value<uint32_t, uint64_t>(heap.walker(), memory_address);
        }

        if(heap.is_x64_target())
        {
            return read_field_value<uint64_t>(heap.walker(), memory_address);
        }

        return std::nullopt;
    }

    std::optional<uint64_t> find_machine_size_field_value(heap::nt_heap const& heap, dbg_help::symbol_type_info const& type, std::wstring_view const field_name, uint64_t const memory_address)
    {
        if(heap.is_x86_target())
        {
            return find_basic_type_field_value_in_type<uint32_t>(heap.walker(), type, field_name, memory_address);
        }

        if(heap.is_x64_target())
        {
            return find_basic_type_field_value_in_type<uint64_t>(heap.walker(), type, field_name, memory_address);
        }

        return std::nullopt;
    }

    dbg_help::symbol_type_info get_type(stream_stack_dump::mini_dump_stack_walk const& walker, std::wstring const& name)
    {
        auto const symbol_info = walker.get_type_info(name);
        if(!symbol_info.has_value())
        {
            throw exceptions::wide_runtime_error{(std::wostringstream{} << "Error: symbol " << name << " not found").str()};
        }

        return symbol_info.value();
    }

    uint64_t get_type_length(dbg_help::symbol_type_info const& type, std::wstring const& type_name)
    {
        if(auto const length_data = type.length(); length_data.has_value())
        {
            return length_data.value();
        }

        throw exceptions::wide_runtime_error{(std::wostringstream{} << "Error: symbol " << type_name << " length not found").str()};
    }

    uint64_t get_field_pointer(stream_stack_dump::mini_dump_stack_walk const& walker, uint64_t const address, dbg_help::symbol_type_info const& type, std::wstring const& type_name, std::wstring const& field_name)
    {
        auto const address_value = find_field_pointer_type_and_value_in_type(walker, type, field_name, address);
        if(!address_value.has_value())
        {
            throw_cant_get_field_data(type_name, field_name);
        }

        auto const pointer_value = std::get<1>(address_value.value());
        if(pointer_value == 0)
        {
            throw_cant_get_field_is_null(type_name, field_name);
        }

        return pointer_value;
    }

    uint64_t get_field_offset(dbg_help::symbol_type_info const& symbol_type, std::wstring const& symbol_name, std::wstring const& field_name)
    {
        if(auto const segment_entry = find_field_in_type(symbol_type, field_name); segment_entry.has_value())
        {
            if(auto const offset_data = segment_entry.value().first.offset(); offset_data.has_value())
            {
                return segment_entry.value().second + offset_data.value();
            }
            throw exceptions::wide_runtime_error{(std::wostringstream{} << "Error: symbol " << symbol_name << " " << field_name << " field has no offset").str()};
        }
        throw exceptions::wide_runtime_error{(std::wostringstream{} << "Error: symbol " << symbol_name << " has no " << field_name << " field").str()};
    }

    void throw_cant_get_field_is_null(std::wstring const& type_name, std::wstring const& field_name)
    {
        throw exceptions::wide_runtime_error{(std::wostringstream{} << "Error: symbol " << type_name << " field " << field_name << " is nullptr").str()};
    }

    void throw_cant_get_field_data(std::wstring const& type_name, std::wstring const& field_name)
    {
        throw exceptions::wide_runtime_error{(std::wostringstream{} << "Error: symbol " << type_name << " can't get " << field_name << " field data").str()};
    }
}

