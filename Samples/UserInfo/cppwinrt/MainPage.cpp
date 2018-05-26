#include "pch.h"
#include "MainPage.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

// TODO: Would like this to be in the SDKTemplate namespace
//       (the issue was that the generated files were in SDKTemplate sub-dir)
//       (could solve by putting that in the include path?)

namespace winrt::UserInfoCppWinRt::implementation
{
    // TODO: In the C++/CX version this is supplied as a property of a partial class
    //       (would that go in our IDL?)
    const wchar_t FEATURE_NAME[] = L"User info C++/WinRT sample";

    MainPage::MainPage()
    {
        InitializeComponent();
        SampleTitle().Text(FEATURE_NAME);
    }

    void MainPage::Button_Click(IInspectable const&, RoutedEventArgs const&)
    {
    }

    void MainPage::ScenarioControl_SelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& args)
    {
    }

    void MainPage::Footer_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
    {
    }

    void MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& args) const
    {
    }
}
