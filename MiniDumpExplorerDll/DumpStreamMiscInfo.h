﻿#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "DumpStreamMiscInfo.g.h"

namespace winrt::MiniDumpExplorer::implementation
{
    struct DumpStreamMiscInfo : DumpStreamMiscInfoT<DumpStreamMiscInfo>
    {
        DumpStreamMiscInfo();
    };
}

namespace winrt::MiniDumpExplorer::factory_implementation
{
    struct DumpStreamMiscInfo : DumpStreamMiscInfoT<DumpStreamMiscInfo, implementation::DumpStreamMiscInfo>
    {
    };
}
