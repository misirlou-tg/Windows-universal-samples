#include "pch.h"
#include "Scenario1_FindUsers.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::SDKTemplate::implementation
{
    Scenario1_FindUsers::Scenario1_FindUsers()
    {
        InitializeComponent();
    }

    int32_t Scenario1_FindUsers::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Scenario1_FindUsers::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void Scenario1_FindUsers::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
