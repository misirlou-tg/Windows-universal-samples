#include "pch.h"
#include "MainPage.h"

using namespace winrt;

namespace winrt::SDKTemplate::implementation
{
    hstring MainPage::FeatureName()
    {
        return L"User info C++/WinRT sample";
    }

    std::vector<MainPage::Scenario> MainPage::Scenarios()
    {
        static Scenario scenarios[] =
        {
            { L"Find users", L"SDKTemplate.Scenario1_FindUsers" },
            { L"Watch users", L"SDKTemplate.Scenario2_WatchUsers" }
        };
        
        std::vector<MainPage::Scenario> ret;;
        for (auto t = 0; t < _countof(scenarios); t++)
        {
            ret.push_back(scenarios[t]);
        }
        return ret;
    }
}
