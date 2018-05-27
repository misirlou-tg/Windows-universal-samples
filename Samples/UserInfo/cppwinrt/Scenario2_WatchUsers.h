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

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario2_WatchUsers : Scenario2_WatchUsersT<Scenario2_WatchUsers, implementation::Scenario2_WatchUsers>
    {
    };
}
