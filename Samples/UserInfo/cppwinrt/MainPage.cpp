#include "pch.h"
#include "MainPage.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UserInfoCppWinRt::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    //void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    //{
    //    myButton().Content(box_value(L"Clicked"));
    //}
}
