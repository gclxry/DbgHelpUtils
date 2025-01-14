﻿#include "symbol_engine_ui.h"

#include <iostream>
#include <sstream>

bool symbol_engine_ui::deferred_symbol_load_cancel([[maybe_unused]] std::wstring_view const& module_name)
{
    return false;
}

void symbol_engine_ui::deferred_symbol_load_partial([[maybe_unused]] std::wstring_view const& module_name)
{
}

void symbol_engine_ui::start_download(std::wstring_view const& module_name)
{
    std::wstringstream ss;
    ss << L"downloading " << module_name << L": ";
    module_ = std::move(ss).str();
    std::wcerr << module_;
    last_percent_.clear();
}

void symbol_engine_ui::download_percent(unsigned const percent)
{
    if (!last_percent_.empty())
    {
        std::wcerr << std::wstring(last_percent_.size(), L'\b');
    }

    std::wstringstream ss;
    ss << percent << L"%";
    std::wcerr << ss.str();
    last_percent_ = std::move(ss).str();
}

void symbol_engine_ui::download_complete()
{
    if (!last_percent_.empty() || !module_.empty())
    {
        std::wstring const clear(last_percent_.size() + module_.size(), L'\b');
        std::wcerr << clear << std::wstring(last_percent_.size() + module_.size(), L' ') << clear;
    }
    last_percent_.clear();
    module_.clear();
}

std::wostream& symbol_engine_ui::log_stream() const
{
    return std::wcerr;
}

bool symbol_engine_ui::symbol_load_debug() const
{
    return false;
}

bool symbol_engine_ui::symbol_load_debug_memory() const
{
    return false;
}
