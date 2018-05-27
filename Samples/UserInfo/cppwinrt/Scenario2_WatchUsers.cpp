#include "pch.h"
#include "Scenario2_WatchUsers.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::SDKTemplate::implementation
{
    Scenario2_WatchUsers::Scenario2_WatchUsers()
    {
        InitializeComponent();
    }

    int32_t Scenario2_WatchUsers::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Scenario2_WatchUsers::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void Scenario2_WatchUsers::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
