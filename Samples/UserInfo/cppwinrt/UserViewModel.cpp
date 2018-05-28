#include "pch.h"
#include "UserViewModel.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Data;

namespace winrt::SDKTemplate::implementation
{
    UserViewModel::UserViewModel(hstring const& userId, hstring const& displayName)
        : userId(userId), displayName(displayName)
    {
    }

    hstring UserViewModel::UserId()
    {
        return userId;
    }

    hstring UserViewModel::DisplayName()
    {
        return displayName;
    }

    void UserViewModel::DisplayName(hstring const& value)
    {
        if (displayName != value)
        {
            displayName = value;
            FirePropertyChanged(L"DisplayName");
        }
    }

    void UserViewModel::FirePropertyChanged(const wchar_t* propertyName)
    {
        propertyChanged(*this, PropertyChangedEventArgs(propertyName));
    }

    event_token UserViewModel::PropertyChanged(PropertyChangedEventHandler const& handler)
    {
        return propertyChanged.add(handler);
    }

    void UserViewModel::PropertyChanged(event_token const& token)
    {
        propertyChanged.remove(token);
    }
}
