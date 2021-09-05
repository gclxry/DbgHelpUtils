﻿#pragma once
#include <cstdint>
#include <experimental/generator>

#include "symbol_type_info.h"

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
    class lfh_segment;
    class nt_heap;

    class lfh_heap
    {
    public:
        lfh_heap(nt_heap const& heap, uint64_t lfh_heap_address);

        [[nodiscard]] nt_heap const& heap() const { return heap_; }
        [[nodiscard]] stream_stack_dump::mini_dump_stack_walk const& walker() const;
        [[nodiscard]] process::process_environment_block const& peb() const;

        [[nodiscard]] uint64_t address() const { return lfh_heap_address_; }

        [[nodiscard]] std::optional<uint64_t> lfh_key() const { return lfh_key_; }
        [[nodiscard]] std::experimental::generator<lfh_segment> lfh_segments() const;

        [[nodiscard]] uint64_t symbol_address() const { return address(); }
        [[nodiscard]] dbg_help::symbol_type_info const& symbol_type() const { return lfh_heap_symbol_type_; }

        static std::wstring const& symbol_name;

    private:
        [[nodiscard]] std::optional<uint64_t> get_lfh_key() const;

    private:
        nt_heap const& heap_;
        uint64_t const lfh_heap_address_;
        dbg_help::symbol_type_info const lfh_heap_symbol_type_;
        std::optional<uint64_t> lfh_key_{get_lfh_key()};
    };
}