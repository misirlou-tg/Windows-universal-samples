#include "pch.h"
#include "MainPage.h"

using namespace winrt;
using namespace Windows::Foundation::Collections;

namespace winrt::UserInfoCppWinRt::implementation
{
    hstring MainPage::FeatureName()
    {
        return L"User info C++/WinRT sample";
    }

    struct Scenario
    {
        hstring Title;
        hstring ClassName;
    };

    StringMap MainPage::Scenarios()
    {
        static Scenario scenarios[] =
        {
            { L"Find users", L"SDKTemplate.Scenario1_FindUsers" },
            { L"Watch users", L"SDKTemplate.Scenario2_WatchUsers" }
        };
        
        StringMap ret;
        for (auto t = 0; t < _countof(scenarios); t++)
        {
            ret.Insert(scenarios[t].Title, scenarios[t].ClassName);
        }
        return ret;
    }
}
