﻿#pragma once
#include <cstdint>
#include <functional>
#include <experimental/generator>

namespace dlg_help_utils
{
    class mini_dump_memory_stream
    {
    public:
        mini_dump_memory_stream() = default;
        mini_dump_memory_stream(std::function<void const*(uint64_t base_address, uint64_t& size, bool enable_module_loading)> get_process_memory_range, uint64_t base_address, uint64_t size, bool enable_module_loading);
        mini_dump_memory_stream(void const* memory, uint64_t size);

        [[nodiscard]] bool eof() const;
        [[nodiscard]] size_t read(void* buffer, size_t length);
        size_t skip(size_t length);
        [[nodiscard]] uint64_t current_address() const { return current_address_; }
        [[nodiscard]] uint64_t length() const { return end_address_ - current_address_; }

        [[nodiscard]] std::experimental::generator<std::pair<void const*,size_t>> ranges();

        template<typename T>
        [[nodiscard]] bool find_pattern(std::function<bool(T, size_t)> const& check_data, std::function<bool(size_t)> const& is_found)
        {
            auto reset_stream = *this;
            size_t index = 0;
            while(!eof() && !is_found(index))
            {
                T check;
                if(read(&check, sizeof(T)) != sizeof(T))
                {
                    break;
                }

                if(check_data(check, index))
                {
                    if(index == 0)
                    {
                        reset_stream = *this;
                    }
                    ++index;
                    if(is_found(index))
                    {
                        return true;
                    }
                }
                else
                {
                    if(index > 0)
                    {
                        *this = reset_stream;
                    }
                    index = 0;
                }
            }

            return is_found(index);
        }

    private:
        template<typename T>
        [[nodiscard]] size_t process_data(size_t length, T op);

    private:
        std::function<void const*(uint64_t base_address, uint64_t& size, bool enable_module_loading)> get_process_memory_range_;
        bool enable_module_loading_{false};
        uint64_t current_address_{};
        uint64_t end_address_{};
        uint8_t const* memory_{nullptr};
        uint8_t const* end_memory_{nullptr};
    };
}
