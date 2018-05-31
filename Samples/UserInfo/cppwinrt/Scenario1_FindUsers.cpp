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

        _currentUser = winrt::make<UserViewModel>(L"curr user id", L"Current User");

        namespace wfc = Windows::Foundation::Collections;
        auto i1 = models.as<wfc::IObservableVector<IInspectable>>();
        i1.VectorChanged([](wfc::IObservableVector<IInspectable> const& sender, wfc::IVectorChangedEventArgs const& args)
        {
            ::OutputDebugStringW((hstring(L"models changed, collectionChange: ") + winrt::to_hstring((int32_t)args.CollectionChange()) + L", index: " + winrt::to_hstring(args.Index()) + L"\n").c_str());
            auto m = sender.GetAt(args.Index());
            auto x = m.try_as<IDependencyObject2>();
            ::OutputDebugStringW(x == nullptr ? L"  * IDependencyObject2 not found\n" : L"  * IDependencyObject2 found!\n");
            auto u = m.as<IUserViewModel>();
            ::OutputDebugStringW((hstring(L"  * user.DisplayName: ") + u.DisplayName() + L"\n").c_str());
        });

        auto i2 = _currentUser.try_as<Windows::UI::Xaml::Data::INotifyPropertyChanged>();
        i2.PropertyChanged([](Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Data::PropertyChangedEventArgs const& args)
        {
            auto n = args.PropertyName();
            ::OutputDebugStringW((hstring(L"_currentUser changed, PropertyName: ") + n + L"\n").c_str());
        });
    }

    static IAsyncAction GetUsersAsync(Windows::Foundation::Collections::IVector<IInspectable> &models, ComboBox userList)
    {
        auto users = co_await User::FindAllAsync();
        auto nextUserNumber = 1;
        std::vector<hstring> results;
        for (auto&& user : users)
        {
            auto displayNameProp = co_await user.GetPropertyAsync(KnownUserProperties::DisplayName());
            auto displayName = winrt::unbox_value<hstring>(displayNameProp);
            if (displayName.empty())
            {
                displayName = hstring(L"User #") + winrt::to_hstring(nextUserNumber++);
            }
            results.push_back(displayName);
        }
        // **************************************************************************************
        // TODO: Replace thread/context switching with: co_await resume_foreground(Dispatcher());
        // **************************************************************************************
        if (userList.Dispatcher().HasThreadAccess())
        {
            for (uint32_t index = 0; index < users.Size(); index++)
            {
                models.Append(winrt::make<SDKTemplate::implementation::UserViewModel>(users.GetAt(index).NonRoamableId(), results[0]));
            }
            userList.SelectedIndex(0);
        }
        else
        {
            userList.Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [&userList, &models, users, results]()
            {
                for (uint32_t index = 0; index < users.Size(); index++)
                {
                    models.Append(winrt::make<SDKTemplate::implementation::UserViewModel>(users.GetAt(index).NonRoamableId(), results[0]));
                }
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
        models.Append(winrt::make<SDKTemplate::implementation::UserViewModel>(L"another user", L"Another User"));
        _currentUser.DisplayName(L"Changed!");
    }

    SDKTemplate::UserViewModel Scenario1_FindUsers::CurrentUser()
    {
        return _currentUser;
    }
}
