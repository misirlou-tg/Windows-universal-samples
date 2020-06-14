#include "pch.h"
#include "Scenario2_WatchUsers.h"

#include "MainPage.h"
#include "UserViewModel.h"
#include "Scenario1_FindUsers.h"
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
            models.Clear();
            StartButton().IsEnabled(true);
            StopButton().IsEnabled(false);

            // The C++/CX version didn't clear the status, but why not?
            if (auto rootPage = MainPage::Current())
            {
                rootPage.NotifyUser(L"", NotifyType::StatusMessage);
            }
        }
    }

    Windows::Foundation::Collections::IObservableVector<IInspectable> Scenario2_WatchUsers::Users()
    {
        return models;
    }

    IAsyncOperation<hstring> Scenario2_WatchUsers::GetDisplayNameOrGenericNameAsync(User user)
    {
        auto displayName = co_await Scenario1_FindUsers::GetDisplayNameOrGenericNameAsync(user, [this]() { return nextUserNumber++; });
        return displayName;
    }

    SDKTemplate::UserViewModel Scenario2_WatchUsers::FindModelByUserId(hstring userId)
    {
        for (auto&& m : models)
        {
            auto model = m.as<SDKTemplate::UserViewModel>();
            if (model.UserId() == userId)
            {
                return model;
            }
        }
        return nullptr;
    }

    IAsyncAction Scenario2_WatchUsers::OnUserAdded(UserWatcher sender, UserChangedEventArgs e)
    {
        UNREFERENCED_PARAMETER(sender);

        // UI work must happen on the UI thread.
        if (auto rootPage = MainPage::Current())
        {
            co_await winrt::resume_foreground(rootPage.Dispatcher());

            // Create the user with "..." as the temporary display name.
            // Add it right away, because it might get removed while the
            // "await GetDisplayNameOrGenericNameAsync()" is running.
            auto model = winrt::make<implementation::UserViewModel>(e.User().NonRoamableId(), L"\u2026");
            // Try to get the display name.
            model.DisplayName(co_await GetDisplayNameOrGenericNameAsync(e.User()));
            models.Append(model);
        }
    }

    IAsyncAction Scenario2_WatchUsers::OnUserUpdated(UserWatcher sender, UserChangedEventArgs e)
    {
        UNREFERENCED_PARAMETER(sender);

        // UI work must happen on the UI thread.
        if (auto rootPage = MainPage::Current())
        {
            co_await winrt::resume_foreground(rootPage.Dispatcher());

            // Look for the user in our collection and update the display name.
            auto model = FindModelByUserId(e.User().NonRoamableId());
            if (model != nullptr)
            {
                model.DisplayName(co_await GetDisplayNameOrGenericNameAsync(e.User()));
            }
        }
    }

    IAsyncAction Scenario2_WatchUsers::OnUserRemoved(UserWatcher sender, UserChangedEventArgs e)
    {
        UNREFERENCED_PARAMETER(sender);

        // UI work must happen on the UI thread.
        if (auto rootPage = MainPage::Current())
        {
            co_await winrt::resume_foreground(rootPage.Dispatcher());

            // Look for the user in our collection and remove it.
            auto model = FindModelByUserId(e.User().NonRoamableId());
            if (model != nullptr)
            {
                uint32_t index;
                if (models.IndexOf(model, index))
                {
                    models.RemoveAt(index);
                }
            }
        }
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
