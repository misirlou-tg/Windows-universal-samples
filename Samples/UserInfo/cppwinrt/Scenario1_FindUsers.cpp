#include "pch.h"
#include "Scenario1_FindUsers.h"

#include "MainPage.h"
#include "UserViewModel.h"
#include "single_threaded_observable_vector.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::System;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media::Imaging;

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

        // Note, the C++/CX version of this DID NOT switch to the UI thread
        co_await winrt::resume_foreground(userList.Dispatcher());
        for (uint32_t index = 0; index < users.Size(); index++)
        {
            models.Append(winrt::make<SDKTemplate::implementation::UserViewModel>(users.GetAt(index).NonRoamableId(), results[0]));
        }
        userList.SelectedIndex(0);
    }

    void Scenario1_FindUsers::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args)
    {
        UNREFERENCED_PARAMETER(args);

        GetUsersAsync(models, UserList());
    }

    static IAsyncAction ShowPropertiesAsync(User user, TextBlock resultsText, Image profileImage)
    {
        auto desiredProperties = std::vector<hstring>
        {
            KnownUserProperties::FirstName(),
            KnownUserProperties::LastName(),
            KnownUserProperties::ProviderName(),
            KnownUserProperties::AccountName(),
            KnownUserProperties::GuestHost(),
            KnownUserProperties::PrincipalName(),
            KnownUserProperties::DomainName(),
            KnownUserProperties::SessionInitiationProtocolUri()
        };

        // We construct a copy of desiredProperties here (instead of using std::move()) because we need desiredProperties later
        auto values = co_await user.GetPropertiesAsync(std::vector(desiredProperties));
        auto result = hstring(L"NonRoamableId: ") + user.NonRoamableId() + L"\n";
        result = result + L"Type: " + winrt::to_hstring(static_cast<int>(user.Type())) + L"\n";
        result = result + L"AuthenticationStatus: " + winrt::to_hstring(static_cast<int>(user.AuthenticationStatus())) + L"\n";
        for (auto&& propertyName : desiredProperties)
        {
            // This works because we know all the properties are strings
            auto propertyValue = winrt::unbox_value<hstring>(values.Lookup(propertyName));
            result = result + propertyName + L": " + propertyValue + L"\n";
        }
        resultsText.Text(result);

        auto streamReference = co_await user.GetPictureAsync(UserPictureSize::Size64x64);
        if (streamReference != nullptr)
        {
            auto stream = co_await streamReference.OpenReadAsync();
            if (stream != nullptr)
            {
                BitmapImage bitmapImage;
                co_await bitmapImage.SetSourceAsync(stream);
                profileImage.Source(bitmapImage);
            }
        }
    }

    void Scenario1_FindUsers::ShowProperties()
    {
        auto model = UserList().SelectedValue().try_as<SDKTemplate::UserViewModel>();
        if (model != nullptr)
        {
            ResultsText().Text(L"");
            ProfileImage().Source(nullptr);
            if (auto rootPage = MainPage::Current())
            {
                rootPage.NotifyUser(L"", NotifyType::StatusMessage);
            }

            User user(nullptr);
            try
            {
                user = User::GetFromId(model.UserId());
            }
            catch (winrt::hresult_error)
            {
                // The C++/CX version of this caught & ignored a Platform::Exception
            }

            if (user != nullptr)
            {
                ShowPropertiesAsync(user, ResultsText(), ProfileImage());
            }
        }
        else
        {
            if (auto rootPage = MainPage::Current())
            {
                rootPage.NotifyUser(L"Could not reacquire the user", NotifyType::ErrorMessage);
            }
        }
    }
}
