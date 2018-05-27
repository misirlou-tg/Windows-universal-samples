//
// Declaration of the Scenario1_FindUsers class.
//

#pragma once

#include "Scenario1_FindUsers.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Scenario1_FindUsers : Scenario1_FindUsersT<Scenario1_FindUsers>
    {
        Scenario1_FindUsers();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario1_FindUsers : Scenario1_FindUsersT<Scenario1_FindUsers, implementation::Scenario1_FindUsers>
    {
    };
}
