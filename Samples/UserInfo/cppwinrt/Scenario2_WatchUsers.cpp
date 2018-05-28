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

    void Scenario2_WatchUsers::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args)
    {
        UNREFERENCED_PARAMETER(args);
    }

    void Scenario2_WatchUsers::StartWatching()
    {
    }

    void Scenario2_WatchUsers::StopWatching()
    {
    }

    Windows::Foundation::Collections::IVector<IInspectable> Scenario2_WatchUsers::Users()
    {
        return winrt::single_threaded_vector<IInspectable>();
    }
}
