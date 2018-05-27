//
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

// TODO: Would like this to be in the SDKTemplate namespace
//       (the issue was that the generated files were in SDKTemplate sub-dir)
//       (could solve by putting that in the include path?)

namespace winrt::UserInfoCppWinRt::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();
        hstring FeatureName();
        Windows::Foundation::Collections::StringMap Scenarios();

        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args);

        void Button_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        void ScenarioControl_SelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& args);
        void Footer_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::UserInfoCppWinRt::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
