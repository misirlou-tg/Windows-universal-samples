#include "pch.h"
#include "Scenario2_WatchUsers.h"

#include "MainPage.h"
#include "single_threaded_observable_vector.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::System;
using namespace Windows::UI::Xaml;

namespace winrt::SDKTemplate::implementation
{
    Scenario2_WatchUsers::Scenario2_WatchUsers()
        : userWatcher(nullptr)
    {
        InitializeComponent();

        models = winrt::make<single_threaded_observable_vector<IInspectable>>();
        UserList().DataContext(models);
    }

    void Scenario2_WatchUsers::OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args)
    {
        UNREFERENCED_PARAMETER(args);

        StopWatching();
    }

    void Scenario2_WatchUsers::StartWatching()
    {
        if (auto rootPage = MainPage::Current())
        {
            rootPage.NotifyUser(L"", NotifyType::StatusMessage);
        }

        nextUserNumber = 1;
        models.Clear();
        userWatcher = User::CreateWatcher();
        userAddedToken = userWatcher.Added({ this, &Scenario2_WatchUsers::OnUserAdded });
        userUpdatedToken = userWatcher.Updated({ this, &Scenario2_WatchUsers::OnUserUpdated });
        userRemovedToken = userWatcher.Removed({ this, &Scenario2_WatchUsers::OnUserRemoved });
        enumerationCompletedToken = userWatcher.EnumerationCompleted({ this, &Scenario2_WatchUsers::OnEnumerationCompleted });
        watcherStoppedToken = userWatcher.Stopped({ this, &Scenario2_WatchUsers::OnWatcherStopped });
        userWatcher.Start();
        StartButton().IsEnabled(false);
        StopButton().IsEnabled(true);
    }

    void Scenario2_WatchUsers::StopWatching()
    {
        if (userWatcher != nullptr)
        {
            // Unregister all event handlers in case events are in flight.
            userWatcher.Added(userAddedToken);
            userWatcher.Updated(userUpdatedToken);
            userWatcher.Removed(userRemovedToken);
            userWatcher.EnumerationCompleted(enumerationCompletedToken);
            userWatcher.Stopped(watcherStoppedToken);
            userWatcher.Stop();
            userWatcher = nullptr;
            StartButton().IsEnabled(true);
            StopButton().IsEnabled(false);

            // The C++/CX version didn't clear the status, but why not?
            if (auto rootPage = MainPage::Current())
            {
                rootPage.NotifyUser(L"", NotifyType::StatusMessage);
            }
        }
    }

    Windows::Foundation::Collections::IVector<IInspectable> Scenario2_WatchUsers::Users()
    {
        return models;
    }

    void Scenario2_WatchUsers::OnUserAdded(UserWatcher sender, UserChangedEventArgs e)
    {
        UNREFERENCED_PARAMETER(sender);
        UNREFERENCED_PARAMETER(e);

        ::OutputDebugStringW(L"OnUserAdded() called\n");
    }

    void Scenario2_WatchUsers::OnUserUpdated(UserWatcher sender, UserChangedEventArgs e)
    {
        UNREFERENCED_PARAMETER(sender);
        UNREFERENCED_PARAMETER(e);

        ::OutputDebugStringW(L"OnUserUpdated() called\n");
    }

    void Scenario2_WatchUsers::OnUserRemoved(UserWatcher sender, UserChangedEventArgs e)
    {
        UNREFERENCED_PARAMETER(sender);
        UNREFERENCED_PARAMETER(e);

        ::OutputDebugStringW(L"OnUserRemoved() called\n");
    }

    IAsyncAction Scenario2_WatchUsers::OnEnumerationCompleted(Windows::System::UserWatcher sender, IInspectable e)
    {
        UNREFERENCED_PARAMETER(sender);
        UNREFERENCED_PARAMETER(e);

        // UI work must happen on the UI thread.
        if (auto rootPage = MainPage::Current())
        {
            co_await winrt::resume_foreground(rootPage.Dispatcher());
            rootPage.NotifyUser(L"Enumeration complete. Watching for changes...", NotifyType::StatusMessage);
        }
    }

    IAsyncAction Scenario2_WatchUsers::OnWatcherStopped(Windows::System::UserWatcher sender, IInspectable e)
    {
        UNREFERENCED_PARAMETER(sender);
        UNREFERENCED_PARAMETER(e);

        // UI work must happen on the UI thread.
        if(auto rootPage = MainPage::Current())
        {
            co_await winrt::resume_foreground(rootPage.Dispatcher());
            StopWatching();
        }
    }
}
