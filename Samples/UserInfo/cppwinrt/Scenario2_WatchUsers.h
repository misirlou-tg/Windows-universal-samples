//
// Declaration of the Scenario2_WatchUsers class.
//

#pragma once

#include "Scenario2_WatchUsers.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Scenario2_WatchUsers : Scenario2_WatchUsersT<Scenario2_WatchUsers>
    {
        Scenario2_WatchUsers();

        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args);

        void StartWatching();
        void StopWatching();

        Windows::Foundation::Collections::IVector<IInspectable> Users();
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario2_WatchUsers : Scenario2_WatchUsersT<Scenario2_WatchUsers, implementation::Scenario2_WatchUsers>
    {
    };
}
