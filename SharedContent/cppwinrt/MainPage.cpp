#include "pch.h"
#include "MainPage.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;

// TODO: Would like this to be in the SDKTemplate namespace
//       (the issue was that the generated files were in SDKTemplate sub-dir)
//       (could solve by putting that in the include path?)

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

            textBlock.Text(winrt::to_hstring(i++) + L") " + s.Key());
            textBlock.Style(style.as<Windows::UI::Xaml::Style>());

            item.Name(s.Value());
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
        auto uriText = winrt::unbox_value<hstring>(buttonTag);
        Windows::System::Launcher::LaunchUriAsync(Uri(uriText));
    }

    void MainPage::NotifyUser(hstring message, NotifyType type)
    {
        UNREFERENCED_PARAMETER(message);
        UNREFERENCED_PARAMETER(type);
    }

    void MainPage::UpdateStatus(hstring message, NotifyType type)
    {
        UNREFERENCED_PARAMETER(message);
        UNREFERENCED_PARAMETER(type);
    }
}
