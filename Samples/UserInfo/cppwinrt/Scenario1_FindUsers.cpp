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

    void Scenario1_FindUsers::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args)
    {
        UNREFERENCED_PARAMETER(args);
    }

    void Scenario1_FindUsers::ShowProperties()
    {
    }
}
