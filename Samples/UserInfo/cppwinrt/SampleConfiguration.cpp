#include "pch.h"
#include <winrt/SDKTemplate.h>
#include "MainPage.h"
#include "SampleConfiguration.h"

using namespace winrt;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation::Collections;
using namespace SDKTemplate;

hstring implementation::MainPage::FEATURE_NAME()
{
    return L"User info C++/WinRT sample";
}

IVector<Scenario> implementation::MainPage::scenariosInner = winrt::single_threaded_observable_vector<Scenario>(
    {
        Scenario{ L"Find users", xaml_typename<SDKTemplate::Scenario1_FindUsers>() },
        Scenario{ L"Watch users", xaml_typename<SDKTemplate::Scenario2_WatchUsers>() },
    });

void winrt::SDKTemplate::App_LaunchCompleted(LaunchActivatedEventArgs const& e)
{
    hstring arguments = e.Arguments();
    if (!arguments.empty())
    {
        implementation::MainPage::Current().Navigate(xaml_typename<Scenario1_FindUsers>(), box_value(L"arguments: " + arguments));
    }
}
