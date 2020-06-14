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

        virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args);

        void StartWatching();
        void StopWatching();

        Windows::Foundation::Collections::IObservableVector<IInspectable> Users();

    private:
        Windows::Foundation::Collections::IObservableVector<IInspectable> models;
        int nextUserNumber;
        Windows::System::UserWatcher userWatcher;

        winrt::event_token userAddedToken;
        winrt::event_token userUpdatedToken;
        winrt::event_token userRemovedToken;
        winrt::event_token enumerationCompletedToken;
        winrt::event_token watcherStoppedToken;

        SDKTemplate::UserViewModel FindModelByUserId(hstring userId);
        Windows::Foundation::IAsyncOperation<hstring> GetDisplayNameOrGenericNameAsync(Windows::System::User user);

        Windows::Foundation::IAsyncAction OnUserAdded(Windows::System::UserWatcher sender, Windows::System::UserChangedEventArgs e);
        Windows::Foundation::IAsyncAction OnUserUpdated(Windows::System::UserWatcher sender, Windows::System::UserChangedEventArgs e);
        Windows::Foundation::IAsyncAction OnUserRemoved(Windows::System::UserWatcher sender, Windows::System::UserChangedEventArgs e);
        Windows::Foundation::IAsyncAction OnEnumerationCompleted(Windows::System::UserWatcher sender, IInspectable e);
        Windows::Foundation::IAsyncAction OnWatcherStopped(Windows::System::UserWatcher sender, IInspectable e);
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario2_WatchUsers : Scenario2_WatchUsersT<Scenario2_WatchUsers, implementation::Scenario2_WatchUsers>
    {
    };
}
