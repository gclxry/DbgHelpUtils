﻿#include "lfh_segment.h"

#include "common_symbol_names.h"
#include "heap_subsegment.h"
#include "lfh_heap.h"
#include "nt_heap.h"
#include "stream_utils.h"

namespace dlg_help_utils::heap
{
    lfh_segment::lfh_segment(lfh_heap const& heap, uint64_t const lfh_segment_address)
    : heap_{heap}
    , lfh_segment_address_{lfh_segment_address}
    , lfh_block_zone_symbol_type_{stream_utils::get_type(heap.walker(), common_symbol_names::lfh_block_zone_structure_symbol_name)}
    , lfh_block_zone_size_{get_lfh_block_zone_size()}
    , heap_subsegment_size_{stream_utils::get_type_length(stream_utils::get_type(heap.walker(), common_symbol_names::heap_subsegment_structure_symbol_name), common_symbol_names::heap_subsegment_structure_symbol_name)}
    {
    }

    size_t lfh_segment::subsegments_count() const
    {
        auto [start_subsegment_address, end_subsegment_address] = get_subsegment_range();
        return (end_subsegment_address - start_subsegment_address) / heap_subsegment_size_;
    }

    std::experimental::generator<heap_subsegment> lfh_segment::subsegments() const
    {
        auto [subsegment_address, end_subsegment_address] = get_subsegment_range();

        while(subsegment_address + heap_subsegment_size_ <= end_subsegment_address)
        {
            heap_subsegment subsegment{heap_, subsegment_address, lfh_block_zone_size_};

            co_yield subsegment;

            subsegment_address += heap_subsegment_size_;
        }
    }

    std::pair<uint64_t, uint64_t> lfh_segment::get_subsegment_range() const
    {
        auto start_subsegment_address = lfh_segment_address_ + lfh_block_zone_size_;
        auto end_subsegment_address{start_subsegment_address};

        if(auto const next_index = stream_utils::find_basic_type_field_value_in_type<uint32_t>(heap_.walker(), lfh_block_zone_symbol_type_, common_symbol_names::lfh_block_zone_next_index_field_symbol_name, lfh_segment_address_); next_index.has_value())
        {
            if(heap_.heap().is_x64_target())
            {
                end_subsegment_address = start_subsegment_address = lfh_segment_address_ + 0x20;
            }

            end_subsegment_address += heap_subsegment_size_ * next_index.value();
        }
        else if(auto const free_pointer = stream_utils::find_field_pointer_value_in_type(heap_.walker(), lfh_block_zone_symbol_type_, common_symbol_names::lfh_block_zone_free_pointer_field_symbol_name, lfh_segment_address_); free_pointer.has_value())
        {
            end_subsegment_address = free_pointer.value();
        }

        return std::make_pair(start_subsegment_address, end_subsegment_address);
    }

    uint64_t lfh_segment::get_lfh_block_zone_size() const
    {
        if(heap_.heap().is_x86_target())
        {
            return 0x10;
        }

        return stream_utils::get_type_length(lfh_block_zone_symbol_type_, common_symbol_names::lfh_block_zone_structure_symbol_name);
    }
}
