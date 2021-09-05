﻿#include "heap_virtual_block.h"

#include "common_symbol_names.h"
#include "heap_entry.h"
#include "nt_heap.h"
#include "stream_utils.h"

namespace dlg_help_utils::heap
{
    std::wstring const& heap_virtual_block::symbol_name = common_symbol_names::heap_virtual_alloc_entry_structure_symbol_name;

    heap_virtual_block::heap_virtual_block(nt_heap const& heap, uint64_t const heap_virtual_block_address)
    : heap_{heap}
    , heap_virtual_block_address_(heap_virtual_block_address)
    , heap_virtual_block_symbol_type_{stream_utils::get_type(walker(), symbol_name)}
    , data_address_{heap_virtual_block_address + stream_utils::get_type_length(heap_virtual_block_symbol_type_, symbol_name)}
    , busy_block_offset_{stream_utils::get_field_offset(heap_virtual_block_symbol_type_, symbol_name, common_symbol_names::heap_virtual_alloc_entry_busy_block_field_symbol_name)}
    {
    }

    stream_stack_dump::mini_dump_stack_walk const& heap_virtual_block::walker() const
    {
        return heap().walker();
    }

    process::process_environment_block const& heap_virtual_block::peb() const
    {
        return heap().peb();
    }

    size_units::base_10::bytes heap_virtual_block::reserved() const
    {
        return size_units::base_10::bytes{stream_utils::get_machine_size_field_value(*this, common_symbol_names::heap_virtual_alloc_entry_reserve_size_field_symbol_name) };
    }

    size_units::base_10::bytes heap_virtual_block::committed() const
    {
        return size_units::base_10::bytes{stream_utils::get_machine_size_field_value(*this, common_symbol_names::heap_virtual_alloc_entry_commit_size_field_symbol_name) };
    }

    std::experimental::generator<heap_entry> heap_virtual_block::entries() const
    {
        auto const committed_size = committed();
        if(auto const reserved_size = reserved(); committed_size > size_units::base_10::bytes{0})
        {
            auto const entry_address = descriptor_address() + busy_block_offset_;
            auto const last_address = address() + committed_size.count();
            auto const last_committed_address = address() + reserved_size.count();

            auto buffer = std::make_shared<uint8_t[]>(heap().granularity());
            if(auto const* entry_data = walker().get_process_memory(entry_address, heap().granularity()); entry_data == nullptr)
            {
                co_yield heap_entry{heap(), entry_address, last_address - entry_address};
            }
            else
            {
                heap().decode_heap_entry(entry_data, buffer.get());

                uint16_t unused_bytes{0};
                if(heap().peb().is_x86_target())
                {
                    memcpy(&unused_bytes, buffer.get(), sizeof(uint16_t));
                }
                if(heap().peb().is_x64_target())
                {
                    memcpy(&unused_bytes, buffer.get() + 8, sizeof(uint16_t));
                }

                if(unused_bytes > committed_size.count())
                {
                    co_yield heap_entry{heap(), entry_address, last_address -  entry_address, heap_entry::UnknownSizeType{}};
                }
                else
                {
                    co_yield heap_entry{heap(), entry_address, last_address, std::move(buffer), static_cast<uint64_t>(committed_size.count()), unused_bytes, heap_entry::VirtualAllocType{} };
                }
            }

            if(last_address < last_committed_address)
            {
                co_yield heap_entry{heap(), last_address, last_committed_address -  last_address};
            }
        }
        else if(reserved_size > size_units::base_10::bytes{0})
        {
            co_yield heap_entry{heap(), address(), static_cast<uint64_t>(reserved_size.count())};
        }
    }
}
