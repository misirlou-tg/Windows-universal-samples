﻿#include "pch.h"
#include "MainPage.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Automation::Peers;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;

namespace winrt::SDKTemplate::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
        SampleTitle().Text(FeatureName());
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
        UNREFERENCED_PARAMETER(args);

        auto scenarioListBox = sender.as<ListBox>();
        auto item = scenarioListBox.SelectedItem().try_as<ListBoxItem>();
        if (item != nullptr)
        {
            // Clear the status block when changing scenarios
            NotifyUser(L"", NotifyType::StatusMessage);

            // Navigate to the selected scenario.
            TypeName scenarioType{ item.Name(), TypeKind::Custom };
            // *******************************************************************
            // TODO: The CPP/CX version passed 'this' as 'parameter' to Navigate()
            //       (this likely won't work, any app class that needs a reference
            //       to this page will have to get it from a static weak reference
            //       that we can initialize with get_weak())
            // *******************************************************************
            ScenarioFrame().Navigate(scenarioType);

            if (Window::Current().Bounds().Width < 640)
            {
                Splitter().IsPaneOpen(false);
            }
        }
    }

    void MainPage::Footer_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
    {
        UNREFERENCED_PARAMETER(args);

        auto button = sender.as<HyperlinkButton>();
        auto buttonTag = button.Tag();
        // buttonTag is actually a IReference<hstring>, access the hstring with .Value()
        // But winrt::unbox_value() does this for us
        auto uriText = winrt::unbox_value<hstring>(buttonTag);
        Windows::System::Launcher::LaunchUriAsync(Uri(uriText));
    }

    IAsyncAction MainPage::NotifyUser(hstring message, NotifyType type)
    {
        co_await winrt::resume_foreground(Dispatcher());
        UpdateStatus(message, type);
    }

    void MainPage::UpdateStatus(hstring message, NotifyType type)
    {
        switch (type)
        {
        case NotifyType::StatusMessage:
            StatusBorder().Background(SolidColorBrush(Windows::UI::Colors::Green()));
            break;
        case NotifyType::ErrorMessage:
            StatusBorder().Background(SolidColorBrush(Windows::UI::Colors::Red()));
            break;
        default:
            break;
        }

        StatusBlock().Text(message);

        // Collapse the StatusBlock if it has no text to conserve real estate.
        if (!StatusBlock().Text().empty())
        {
            StatusBorder().Visibility(Windows::UI::Xaml::Visibility::Visible);
            StatusPanel().Visibility(Windows::UI::Xaml::Visibility::Visible);
        }
        else
        {
            StatusBorder().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
            StatusPanel().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
        }

        // Raise an event if necessary to enable a screen reader to announce the status update.
        auto peer = FrameworkElementAutomationPeer::FromElement(StatusBlock()).try_as<FrameworkElementAutomationPeer>();
        if (peer != nullptr)
        {
            peer.RaiseAutomationEvent(AutomationEvents::LiveRegionChanged);
        }
    }
}
