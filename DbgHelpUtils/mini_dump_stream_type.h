﻿#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include "windows_setup.h"
#include <DbgHelp.h>
#include <string>

namespace dlg_help_utils::mini_dump_stream_type
{
    std::wstring to_string(MINIDUMP_STREAM_TYPE type);
    std::wstring to_enum_string(MINIDUMP_STREAM_TYPE type);
    MINIDUMP_STREAM_TYPE from_string(std::wstring const& type);
}
