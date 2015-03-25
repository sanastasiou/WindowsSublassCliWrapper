#ifndef WINDOWS_SUBCLASS_H
#define WINDOWS_SUBCLASS_H

#include <Windows.h>
#include <Commctrl.h>
#include <string>
#include <sstream>

namespace WindowsSubclassWrapper
{
    class WindowsSubclass
    {
    public:
        WindowsSubclass(bool(*handler)(UINT msg), HWND windowHandle) :
            _hasError(false),
            _hWnd(windowHandle)
        {
            _handler = handler;
        }

        void OnSafeSubclass(HWND hWnd)
        {
            _hWnd = hWnd;
            UINT_PTR uIdSubclass = 0;
            if (!SetWindowSubclass(_hWnd, NewSafeBtnProc, uIdSubclass, 0))
            {
                ReportError(L"SetWindowSubclass in OnSafeSubclass");
                _hasError = true;
                return;
            }
            _hasError = false;
        }

        inline bool HasError()
        {
            return _hasError;
        }

        std::wstring LastError()
        {
            return _lastError;
        }
    private:
        bool _hasError;
        std::wstring _lastError;
        HWND _hWnd;                                  //!< Handle of the windows we want to sublcass.
        static bool(*_handler)(UINT, WPARAM, LPARAM);//!< External message handler.

        void ReportError(LPCWSTR pszFunction, DWORD dwError = NO_ERROR)
        {
            std::wstringstream aErrorStream;

            aErrorStream << "Function" << pszFunction << " failed : " << dwError;

            _lastError = aErrorStream.str();
        }        

        void OnSafeUnsubclass(HWND hWnd)
        {
            UINT_PTR uIdSubclass = 0;
            if (!RemoveWindowSubclass(_hWnd, NewSafeBtnProc, uIdSubclass))
            {
                ReportError(L"RemoveWindowSubclass in OnSafeUnsubclass");
                return;
            }
        }

        static LRESULT CALLBACK NewSafeBtnProc(HWND hButton,
            UINT message,
            WPARAM wParam,
            LPARAM lParam,
            UINT_PTR uIdSubclass,
            DWORD_PTR dwRefData)
        {
            switch (message)
            {
            case WM_NCDESTROY:
                // You must remove your window subclass before the window being 
                // subclassed is destroyed. This is typically done either by removing 
                // the subclass once your temporary need has passed, or if you are 
                // installing a permanent subclass, by inserting a call to 
                // RemoveWindowSubclass inside the subclass procedure itself:
                RemoveWindowSubclass(hButton, NewSafeBtnProc, uIdSubclass);
                return DefSubclassProc(hButton, message, wParam, lParam);
            default:
                //return should be overriden by an exernal handle here
                if (!_handler(message, wParam, lParam))
                {
                    return DefSubclassProc(hButton, message, wParam, lParam);
                }
                else
                {
                    //do not propagate message
                    return TRUE;
                }
            }
        }
    };
} //namespace WindowsSubclassWrapper

#endif //#ifndef WINDOWS_SUBCLASS_H 