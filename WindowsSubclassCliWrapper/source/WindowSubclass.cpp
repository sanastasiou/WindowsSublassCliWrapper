#include "WindowSubclass.h"

namespace WindowsSubclassWrapper
{
    void WindowsSubclass::ReportError(LPCWSTR pszFunction, DWORD dwError)
    {
        std::wstringstream aErrorStream;

        aErrorStream << "Function" << pszFunction << " failed : " << dwError;

        _lastError = aErrorStream.str();
    }

    void WindowsSubclass::OnSafeUnsubclass(HWND hWnd)
    {
        UINT_PTR uIdSubclass = 0;
        if (!RemoveWindowSubclass(_hWnd, NewSafeBtnProc, uIdSubclass))
        {
            ReportError(L"RemoveWindowSubclass in OnSafeUnsubclass");
            return;
        }
    }
}