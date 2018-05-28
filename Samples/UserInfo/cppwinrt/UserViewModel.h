//
// Declaration of the UserViewModel class.
//

#pragma once

#include "UserViewModel.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct UserViewModel : UserViewModelT<UserViewModel>
    {
        UserViewModel() = delete;
        UserViewModel(hstring const& userId, hstring const& displayName);

        hstring UserId();
        hstring DisplayName();
        void DisplayName(hstring const& value);

        event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(event_token const& token);

    private:
        void FirePropertyChanged(const wchar_t* propertyName);

        hstring userId;
        hstring displayName;
        event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged;
    };
}
