﻿#include "pch.h"
#include "DumpStreamMiscInfoView.h"
#if __has_include("DumpStreamMiscInfoView.g.cpp")
#include "DumpStreamMiscInfoView.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::MiniDumpExplorer::implementation
{
    DumpStreamMiscInfoView::DumpStreamMiscInfoView(IDumpFileStreamMiscInfo stream)
        : stream_{stream}
    {
        InitializeComponent();
    }

    IDumpFileStreamMiscInfo DumpStreamMiscInfoView::Stream() const
    {
        return stream_;
    }
}
