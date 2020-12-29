﻿#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "DumpStreamSystemMemoryInfo.g.h"

namespace winrt::MiniDumpExplorer::implementation
{
    struct DumpStreamSystemMemoryInfo : DumpStreamSystemMemoryInfoT<DumpStreamSystemMemoryInfo>
    {
        DumpStreamSystemMemoryInfo();
    };
}

namespace winrt::MiniDumpExplorer::factory_implementation
{
    struct DumpStreamSystemMemoryInfo : DumpStreamSystemMemoryInfoT<DumpStreamSystemMemoryInfo, implementation::DumpStreamSystemMemoryInfo>
    {
    };
}
