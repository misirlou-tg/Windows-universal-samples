Outstanding issues:
  1. When I made the latest .vcxproj changes, I twice got an error that Scenario1's debug
     info is corrupt (I had seen errors like this spuriously after switching to VS 2019).
     Don't know if this is a problem with the changes or a problem with the tools.
  2. I couldn't get the C++/WinRT project to build from the command line. It would get
     an error about a missing file in Assets.
     - This happens when it is 'processing' the App manifest.
     - Could try to find if there is a different target to build to not do this?
     - Could make the App manifest like the other sample C++/WinRT apps?

Found these by searching "c++ winrt xaml"
https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/binding-property
https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/binding-collection

Also see
https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/get-started#xaml-applications
  Be aware that XAML works best with programming languages that offer reflection.
  In C++/WinRT, you sometimes have to do a little extra work in order to interoperate
  with the XAML framework. All of those cases are covered in the documentation.
  Good places to start are [...]
