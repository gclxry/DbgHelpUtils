﻿#include "process_heap_entry.h"

#include "crt_entry.h"
#include "dph_entry.h"
#include "heap_entry.h"
#include "heap_lfh_entry.h"
#include "heap_vs_entry.h"
#include "large_alloc_entry.h"
#include "page_range_descriptor.h"
#include "process_environment_block.h"

namespace dlg_help_utils::heap
{
    process_heap_entry::process_heap_entry(dph_entry const& entry)
    : peb_{entry.peb()}
    , user_address_{entry.user_address()}
    , user_size_{entry.user_requested_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , block_start_address_{entry.virtual_block_address()}
    , block_end_address_{block_start_address_ + entry.virtual_block_size().count()}
    {
    }

    process_heap_entry::process_heap_entry(heap_entry const& entry)
    : peb_{entry.peb()}
    , user_address_{entry.user_address()}
    , user_size_{entry.user_requested_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , block_start_address_{get_nt_heap_entry_block_start(entry)}
    , block_end_address_{block_start_address_ + get_nt_heap_entry_block_size(entry)}
    {
    }

    process_heap_entry::process_heap_entry(heap_lfh_entry const& entry)
    : peb_{entry.peb()}
    , user_address_{entry.user_address()}
    , user_size_{entry.user_requested_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , block_start_address_{entry.block_address()}
    , block_end_address_{block_start_address_ + entry.block_size().count()}
    {
    }

    process_heap_entry::process_heap_entry(page_range_descriptor const& entry)
    : peb_{entry.peb()}
    , user_address_{entry.user_address()}
    , user_size_{entry.user_requested_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , block_start_address_{entry.block_address()}
    , block_end_address_{block_start_address_ + entry.block_size().count()}
    {
    }

    process_heap_entry::process_heap_entry(heap_vs_entry const& entry)
    : peb_{entry.peb()}
    , user_address_{entry.uncommitted_range() ? entry.block_address() : entry.user_address()}
    , user_size_{entry.uncommitted_range() ? size_units::base_10::bytes{entry.block_size()} : entry.user_requested_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , block_start_address_{entry.block_address()}
    , block_end_address_{block_start_address_ + entry.block_size()}
    {
    }

    process_heap_entry::process_heap_entry(large_alloc_entry const& entry)
    : peb_{entry.peb()}
    , user_address_{entry.user_address()}
    , user_size_{entry.user_requested_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , block_start_address_{entry.block_address()}
    , block_end_address_{block_start_address_ + entry.block_size()}
    {
    }

    process_heap_entry::process_heap_entry(dph_entry const& entry, crt_entry const& crt_block)
    : peb_{entry.peb()}
    , user_address_{crt_block.user_address()}
    , user_size_{crt_block.data_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , file_name_{crt_block.filename()}
    , line_number_{crt_block.line_number()}
    , block_start_address_{entry.virtual_block_address()}
    , block_end_address_{block_start_address_ + entry.virtual_block_size().count()}
    {
    }

    process_heap_entry::process_heap_entry(heap_entry const& entry, crt_entry const& crt_block)
    : peb_{entry.peb()}
    , user_address_{crt_block.user_address()}
    , user_size_{crt_block.data_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , file_name_{crt_block.filename()}
    , line_number_{crt_block.line_number()}
    , block_start_address_{get_nt_heap_entry_block_start(entry)}
    , block_end_address_{block_start_address_ + get_nt_heap_entry_block_size(entry)}
    {
    }

    process_heap_entry::process_heap_entry(heap_lfh_entry const& entry, crt_entry const& crt_block)
    : peb_{entry.peb()}
    , user_address_{crt_block.user_address()}
    , user_size_{crt_block.data_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , file_name_{crt_block.filename()}
    , line_number_{crt_block.line_number()}
    , block_start_address_{entry.block_address()}
    , block_end_address_{block_start_address_ + entry.block_size().count()}
    {
    }

    process_heap_entry::process_heap_entry(page_range_descriptor const& entry, crt_entry const& crt_block)
    : peb_{entry.peb()}
    , user_address_{crt_block.user_address()}
    , user_size_{crt_block.data_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , file_name_{crt_block.filename()}
    , line_number_{crt_block.line_number()}
    , block_start_address_{entry.block_address()}
    , block_end_address_{block_start_address_ + entry.block_size().count()}
    {
    }

    process_heap_entry::process_heap_entry(heap_vs_entry const& entry, crt_entry const& crt_block)
    : peb_{entry.peb()}
    , user_address_{crt_block.user_address()}
    , user_size_{crt_block.data_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , file_name_{crt_block.filename()}
    , line_number_{crt_block.line_number()}
    , block_start_address_{entry.block_address()}
    , block_end_address_{block_start_address_ + entry.block_size()}
    {
    }

    process_heap_entry::process_heap_entry(large_alloc_entry const& entry, crt_entry const& crt_block)
    : peb_{entry.peb()}
    , user_address_{crt_block.user_address()}
    , user_size_{crt_block.data_size()}
    , allocation_stack_trace_{entry.allocation_stack_trace()}
    , file_name_{crt_block.filename()}
    , line_number_{crt_block.line_number()}
    , block_start_address_{entry.block_address()}
    , block_end_address_{block_start_address_ + entry.block_size()}
    {
    }

    uint64_t process_heap_entry::user_address() const
    {
        if(user_address_ == 0)
        {
            return block_start_address_;
        }
        return user_address_;
    }

    size_units::base_10::bytes process_heap_entry::user_requested_size() const
    {
        if(user_address_ == 0)
        {
            return  size_units::base_10::bytes{block_end_address_ - block_start_address_};
        }
        return user_size_;
    }

    mini_dump_memory_stream process_heap_entry::user_data() const
    {
        uint64_t const size = user_requested_size().count();
        return peb_.walker().get_process_memory_stream(user_address(), size);
    }

    bool process_heap_entry::contains_address(uint64_t const address) const
    {
        return address >= block_start_address_ && address < block_end_address_;
    }

    uint64_t process_heap_entry::get_nt_heap_entry_block_start(heap_entry const& entry) const
    {
        if(user_address_ == 0)
        {
            return entry.address();
        }

        return user_address_;
    }

    uint64_t process_heap_entry::get_nt_heap_entry_block_size(heap_entry const& entry) const
    {
        if(user_address_ == 0)
        {
            return entry.size().count();
        }
        return user_size_.count();
    }
}
