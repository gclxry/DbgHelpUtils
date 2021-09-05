﻿#pragma once
#include <cstdint>

#include "size_units.h"

namespace dlg_help_utils::process
{
    class process_environment_block;
}

namespace dlg_help_utils::stream_stack_dump
{
    class mini_dump_stack_walk;
}

namespace dlg_help_utils::heap
{
    class heap_lfh_context;

    class heap_lfh_entry
    {
    public:
        heap_lfh_entry(heap_lfh_context const& heap, uint64_t heap_lfh_entry_address, size_units::base_10::bytes block_size, bool allocated, bool has_unused_bytes);

        [[nodiscard]] heap_lfh_context const& heap() const { return heap_; }
        [[nodiscard]] stream_stack_dump::mini_dump_stack_walk const& walker() const;
        [[nodiscard]] process::process_environment_block const& peb() const;

        [[nodiscard]] uint64_t heap_lfh_entry_address() const { return heap_lfh_entry_address_; }

        [[nodiscard]] size_units::base_10::bytes block_size() const { return block_size_; }
        [[nodiscard]] bool allocated() const { return allocated_; }
        [[nodiscard]] bool has_unused_bytes() const { return has_unused_bytes_; }
        [[nodiscard]] size_units::base_10::bytes unused_bytes() const { return unused_bytes_; }

        [[nodiscard]] uint64_t user_address() const;
        [[nodiscard]] size_units::base_10::bytes user_size() const;

    private:
        [[nodiscard]] size_units::base_10::bytes get_unused_bytes() const;
        [[nodiscard]] int64_t read_front_padding_size() const;

    private:
        heap_lfh_context const& heap_;
        uint64_t const heap_lfh_entry_address_;
        size_units::base_10::bytes const block_size_;
        bool const allocated_;
        bool const has_unused_bytes_;
        size_units::base_10::bytes const unused_bytes_;

    };
}
