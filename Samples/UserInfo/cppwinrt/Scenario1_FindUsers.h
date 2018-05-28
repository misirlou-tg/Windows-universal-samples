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

        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args);

        void ShowProperties();

    private:
        Windows::Foundation::Collections::IVector<SDKTemplate::UserViewModel> models;
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario1_FindUsers : Scenario1_FindUsersT<Scenario1_FindUsers, implementation::Scenario1_FindUsers>
    {
    };
}
