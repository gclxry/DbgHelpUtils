﻿#include "list_entry_walker.h"

#include "common_symbol_names.h"
#include "stream_utils.h"

namespace dlg_help_utils::ntdll_utilities
{
    std::wstring const& list_entry_walker::symbol_name = common_symbol_names::list_entry_structure_symbol_name;

    list_entry_walker::list_entry_walker(stream_stack_dump::mini_dump_stack_walk const& walker, uint64_t const start_address, std::wstring const& entry_symbol_name, std::wstring const& entry_field_name, std::function<uint64_t (uint64_t, uint64_t)> address_decoder)
    : walker_{walker}
    , start_address_{start_address}
    , address_decoder_{std::move(address_decoder)}
    , list_entry_symbol_type_{stream_utils::get_type(walker_, symbol_name)}
    , list_entry_entry_offset_{stream_utils::get_field_offset(stream_utils::get_type(walker_, entry_symbol_name), entry_symbol_name, entry_field_name)}
    {
    }

    std::experimental::generator<uint64_t> list_entry_walker::entries() const
    {
        auto const& flink_field = common_symbol_names::list_entry_flink_field_symbol_name;
        auto flink = stream_utils::get_field_pointer_raw(walker_, start_address_, list_entry_symbol_type_, symbol_name, flink_field);
        if(address_decoder_)
        {
            flink = address_decoder_(flink, start_address_);
        }
        if(flink == 0)
        {
            co_return;
        }

        while(flink != start_address_)
        {
            co_yield flink - list_entry_entry_offset_;

            auto const parent = flink;
            flink = stream_utils::get_field_pointer(walker_, parent, list_entry_symbol_type_, symbol_name, flink_field);
            if(address_decoder_)
            {
                flink = address_decoder_(flink, parent);
            }
        }
    }
}
