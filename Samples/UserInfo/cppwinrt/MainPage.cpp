﻿#include "pch.h"
#include "MainPage.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

// TODO: Would like this to be in the SDKTemplate namespace
//       (the issue was that the generated files were in SDKTemplate sub-dir)
//       (could solve by putting that in the include path?)

namespace winrt::UserInfoCppWinRt::implementation
{
    // TODO: In the C++/CX version this is supplied as a property of a partial class
    //       (would that go in our IDL?)
    const wchar_t FEATURE_NAME[] = L"User info C++/WinRT sample";

    // TODO: In the C++/CX version this is supplied as a property of a partial class
    //       (would that go in our IDL?)
    struct Scenario
    {
        hstring Title;
        hstring ClassName;
    };
    winrt::array_view<Scenario> Scenarios()
    {
        static Scenario scenarios[] =
        {
            { L"Find users", L"SDKTemplate.Scenario1_FindUsers" },
            { L"Watch users", L"SDKTemplate.Scenario2_WatchUsers" }
        };
        return scenarios;
    }

    MainPage::MainPage()
    {
        InitializeComponent();
        SampleTitle().Text(FEATURE_NAME);
    }

    void MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args)
    {
        UNREFERENCED_PARAMETER(args);

        std::vector<IInspectable> itemCollection;
        auto i = 1;
        for (auto const& s : Scenarios())
        {
            // Create a textBlock to hold the content and apply the ListItemTextStyle from Styles.xaml
            TextBlock textBlock;
            ListBoxItem item;
            auto style = Application::Current().Resources().Lookup(winrt::box_value(L"ListItemTextStyle"));

            textBlock.Text(winrt::to_hstring(i++) + L") " + s.Title);
            textBlock.Style(style.as<Windows::UI::Xaml::Style>());

            item.Name(s.ClassName);
            item.Content(textBlock);
            itemCollection.push_back(item);
        }
        ScenarioControl().ItemsSource(winrt::single_threaded_vector(std::move(itemCollection)).GetView());
    }

    void MainPage::Button_Click(IInspectable const& sender, RoutedEventArgs const& args)
    {
        UNREFERENCED_PARAMETER(sender);
        UNREFERENCED_PARAMETER(args);

        Splitter().IsPaneOpen(!Splitter().IsPaneOpen());
    }

    void MainPage::ScenarioControl_SelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& args)
    {
        UNREFERENCED_PARAMETER(sender);
        UNREFERENCED_PARAMETER(args);
    }

    void MainPage::Footer_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
    {
        UNREFERENCED_PARAMETER(args);

        auto button = sender.as<HyperlinkButton>();
        auto buttonTag = button.Tag();
        auto uriText = winrt::unbox_value<hstring>(buttonTag);
        Windows::System::Launcher::LaunchUriAsync(Uri(uriText));
    }
}
