﻿//
// Declaration of the Scenario2_WatchUsers class.
//

#pragma once

#include "Scenario2_WatchUsers.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Scenario2_WatchUsers : Scenario2_WatchUsersT<Scenario2_WatchUsers>
    {
        Scenario2_WatchUsers();

        virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args);

        void StartWatching();
        void StopWatching();

        Windows::Foundation::Collections::IVector<IInspectable> Users();

    private:
        Windows::Foundation::Collections::IVector<IInspectable> models;
        int nextUserNumber;
        Windows::System::UserWatcher userWatcher;

        winrt::event_token userAddedToken;
        winrt::event_token userUpdatedToken;
        winrt::event_token userRemovedToken;
        winrt::event_token enumerationCompletedToken;
        winrt::event_token watcherStoppedToken;

        void OnUserAdded(Windows::System::UserWatcher sender, Windows::System::UserChangedEventArgs e);
        void OnUserUpdated(Windows::System::UserWatcher sender, Windows::System::UserChangedEventArgs e);
        void OnUserRemoved(Windows::System::UserWatcher sender, Windows::System::UserChangedEventArgs e);
        void OnEnumerationCompleted(Windows::System::UserWatcher sender, IInspectable e);
        void OnWatcherStopped(Windows::System::UserWatcher sender, IInspectable e);
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario2_WatchUsers : Scenario2_WatchUsersT<Scenario2_WatchUsers, implementation::Scenario2_WatchUsers>
    {
    };
}
