﻿#include "heap_vs_entry.h"

#include "common_symbol_names.h"
#include "segment_heap.h"
#include "stream_utils.h"

namespace dlg_help_utils::heap
{
    std::wstring const& heap_vs_entry::symbol_name = common_symbol_names::heap_vs_chunk_header_structure_symbol_name;

    heap_vs_entry::heap_vs_entry(segment_heap const& heap, uint64_t const heap_vs_entry_address, std::unique_ptr<uint8_t[]> buffer, uint16_t const previous_size)
    : heap_{heap}
    , heap_vs_entry_address_{heap_vs_entry_address}
    , buffer_{std::move(buffer)}
    , heap_vs_chunk_header_symbol_type_{stream_utils::get_type(walker(), symbol_name)}
    , heap_vs_chunk_header_length_{stream_utils::get_type_length(heap_vs_chunk_header_symbol_type_, symbol_name)}
    , size_{get_size()}
    , previous_size_{get_previous_size()}
    , is_valid_{get_is_valid(previous_size)}
    {
    }

    heap_vs_entry::heap_vs_entry(segment_heap const& heap, uint64_t const heap_vs_entry_address, std::unique_ptr<uint8_t[]> buffer)
    : heap_{heap}
    , heap_vs_entry_address_{heap_vs_entry_address}
    , buffer_{std::move(buffer)}
    , heap_vs_chunk_header_symbol_type_{stream_utils::get_type(walker(), symbol_name)}
    , heap_vs_chunk_header_length_{stream_utils::get_type_length(heap_vs_chunk_header_symbol_type_, symbol_name)}
    , size_{get_size()}
    , previous_size_{get_previous_size()}
    {
    }

    heap_vs_entry::heap_vs_entry(segment_heap const& heap, uint64_t const heap_vs_entry_address, uint64_t const uncommitted_size)
    : heap_{heap}
    , heap_vs_entry_address_{heap_vs_entry_address}
    , heap_vs_chunk_header_symbol_type_{stream_utils::get_type(walker(), symbol_name)}
    , heap_vs_chunk_header_length_{stream_utils::get_type_length(heap_vs_chunk_header_symbol_type_, symbol_name)}
    , size_{uncommitted_size}
    , uncommitted_range_{true}
    {
    }

    stream_stack_dump::mini_dump_stack_walk const& heap_vs_entry::walker() const
    {
        return heap().walker();
    }

    process::process_environment_block const& heap_vs_entry::peb() const
    {
        return heap().peb();
    }

    uint16_t heap_vs_entry::memory_cost() const
    {
        return static_cast<uint16_t>(stream_utils::get_bit_field_value_from_buffer<uint32_t>(*this, common_symbol_names::heap_vs_chunk_header_sizes_memory_cost_field_symbol_name, buffer_.get()));
    }

    bool heap_vs_entry::allocated() const
    {
        return stream_utils::get_bit_field_value_from_buffer<uint32_t>(*this, common_symbol_names::heap_vs_chunk_header_sizes_allocated_field_symbol_name, buffer_.get()) != 0;
    }

    uint8_t heap_vs_entry::segment_page_offset() const
    {
        return static_cast<uint8_t>(stream_utils::get_bit_field_value_from_buffer<uint32_t>(*this, common_symbol_names::heap_vs_chunk_header_encoded_segment_page_offset_field_symbol_name, buffer_.get()));
    }

    bool heap_vs_entry::has_unused_bytes() const
    {
        return stream_utils::get_bit_field_value_from_buffer<uint32_t>(*this, common_symbol_names::heap_vs_chunk_header_unused_bytes_field_symbol_name, buffer_.get()) != 0x0;
    }

    size_units::base_10::bytes heap_vs_entry::unused_bytes() const
    {
        if(!has_unused_bytes() || !allocated())
        {
            return size_units::base_10::bytes{0};
        }

        auto const unused_bytes_address = heap_vs_entry_address() + size().count() - 0x02;
        auto const unused_bytes_value = stream_utils::read_field_value<uint16_t>(walker(), unused_bytes_address);
        if(!unused_bytes_value.has_value())
        {
            return size_units::base_10::bytes{0};
        }
        if((unused_bytes_value.value() & 0x8000) == 0x8000)
        {
            // high bit set means 1 byte length...
            return size_units::base_10::bytes{1};
        }

        return size_units::base_10::bytes{unused_bytes_value.value()};
    }

    bool heap_vs_entry::skip_during_walk() const
    {
        return stream_utils::get_bit_field_value_from_buffer<uint32_t>(*this, common_symbol_names::heap_vs_chunk_header_skip_during_walk_field_symbol_name, buffer_.get()) != 0x0;
    }

    uint32_t heap_vs_entry::spare() const
    {
        return stream_utils::get_bit_field_value_from_buffer<uint32_t>(*this, common_symbol_names::heap_vs_chunk_header_spare_field_symbol_name, buffer_.get());
    }

    uint32_t heap_vs_entry::allocated_chunk_bits() const
    {
        return stream_utils::get_field_value_from_buffer<uint32_t>(*this, common_symbol_names::heap_vs_chunk_header_allocated_chunk_bits_field_symbol_name, buffer_.get());
    }

    uint64_t heap_vs_entry::user_address() const
    {
        return heap_vs_entry_address() + heap_vs_chunk_header_length_ + read_front_padding_size();
    }

    size_units::base_10::bytes heap_vs_entry::user_size() const
    {
        auto requested_user_size = size().count() - heap_vs_chunk_header_length_ - read_front_padding_size();
        if(has_unused_bytes())
        {
            requested_user_size -= unused_bytes().count();
        }

        return size_units::base_10::bytes{requested_user_size};
    }

    uint16_t heap_vs_entry::raw_size() const
    {
        return static_cast<uint16_t>(stream_utils::get_bit_field_value_from_buffer<uint32_t>(*this, common_symbol_names::heap_vs_chunk_header_sizes_unsafe_size_field_symbol_name, buffer_.get()));
    }

    size_units::base_10::bytes heap_vs_entry::get_size() const
    {
        return size_units::base_10::bytes{raw_size() << heap().unit_shift_amount()};
    }

    size_units::base_10::bytes heap_vs_entry::get_previous_size() const
    {
        return size_units::base_10::bytes{static_cast<uint64_t>(get_previous_size_raw()) << heap().unit_shift_amount()};
    }

    uint16_t heap_vs_entry::get_previous_size_raw() const
    {
        return static_cast<uint16_t>(stream_utils::get_bit_field_value_from_buffer<uint32_t>(*this, common_symbol_names::heap_vs_chunk_header_sizes_unsafe_prev_size_field_symbol_name, buffer_.get()));
    }

    bool heap_vs_entry::get_is_valid(uint16_t const previous_size) const
    {
        return get_previous_size_raw() == previous_size;
    }

    uint64_t heap_vs_entry::read_front_padding_size() const
    {
        if(!allocated())
        {
            return 0;
        }

        return stream_utils::read_field_value<uint16_t>(walker(), heap_vs_entry_address() + heap_vs_chunk_header_length_).value_or(0);
    }
}