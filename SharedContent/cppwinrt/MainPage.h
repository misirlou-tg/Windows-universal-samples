//
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace winrt::SDKTemplate::implementation
{
    enum NotifyType
    {
        StatusMessage,
        ErrorMessage
    };

    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args);

        void Button_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        void ScenarioControl_SelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& args);
        void Footer_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);

        Windows::Foundation::IAsyncAction NotifyUser(hstring message, NotifyType type);

    private:
        struct Scenario
        {
            hstring Title;
            hstring ClassName;
        };

        static hstring FeatureName();
        static std::vector<Scenario> Scenarios();

        void UpdateStatus(hstring message, NotifyType type);
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
