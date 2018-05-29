#include "pch.h"
#include "Scenario1_FindUsers.h"

#include "UserViewModel.h"
#include "single_threaded_observable_vector.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::System;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::SDKTemplate::implementation
{
    Scenario1_FindUsers::Scenario1_FindUsers()
    {
        InitializeComponent();

        models = winrt::make<SDKTemplate::implementation::single_threaded_observable_vector<IInspectable>>();
        UserList().DataContext(models);
    }

    static IAsyncAction GetUsersAsync(Windows::Foundation::Collections::IVector<IInspectable> &models, ComboBox userList)
    {
        auto users = co_await User::FindAllAsync();
        auto nextUserNumber = 1;
        for (auto&& user : users)
        {
            auto displayNameProp = co_await user.GetPropertyAsync(KnownUserProperties::DisplayName());
            auto displayName = winrt::unbox_value<hstring>(displayNameProp);
            if (displayName.empty())
            {
                displayName = hstring(L"User #") + winrt::to_hstring(nextUserNumber++);
            }

            models.Append(winrt::make<SDKTemplate::implementation::UserViewModel>(user.NonRoamableId(), displayName));
        }
        // **************************************************************************************
        // TODO: Replace thread/context switching with: co_await resume_foreground(Dispatcher());
        // **************************************************************************************
        if (userList.Dispatcher().HasThreadAccess())
        {
            userList.SelectedIndex(0);
        }
        else
        {
            userList.Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [&userList, &models]()
            {
                userList.SelectedIndex(0);
            });
        }
    }

    void Scenario1_FindUsers::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args)
    {
        UNREFERENCED_PARAMETER(args);

        GetUsersAsync(models, UserList());
    }

    void Scenario1_FindUsers::ShowProperties()
    {
    }
}
