//
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

// TODO: Would like this to be in the SDKTemplate namespace
//       (the issue was that the generated files were in SDKTemplate sub-dir)
//       (could solve by putting that in the include path?)

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

        void NotifyUser(hstring message, NotifyType type);

    private:
        static hstring FeatureName();
        static Windows::Foundation::Collections::StringMap Scenarios();

        void UpdateStatus(hstring message, NotifyType type);
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
