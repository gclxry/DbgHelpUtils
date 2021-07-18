﻿#pragma once
// ReSharper disable once CppUnusedIncludeDirective
#include "windows_setup.h"
#include <DbgHelp.h>
#include <string_view>

namespace dlg_help_utils
{
    class mini_dump;

    class stream_unloaded_module
    {
    public:
        explicit stream_unloaded_module(mini_dump const& dump, MINIDUMP_UNLOADED_MODULE const& module);

        MINIDUMP_UNLOADED_MODULE const* operator->() const { return &module_; }
        [[nodiscard]] std::wstring_view const& name() const { return name_; }

    private:
        MINIDUMP_UNLOADED_MODULE const& module_;
        std::wstring_view name_;
    };
}
