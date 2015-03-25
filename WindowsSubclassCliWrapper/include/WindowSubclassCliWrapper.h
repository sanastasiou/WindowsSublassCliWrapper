#pragma once

#include "WindowSubclass.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace WindowsSubclassWrapper
{
    public ref class WindowSubclassCliWrapper abstract
    {
    private:
        [System::Runtime::InteropServices::UnmanagedFunctionPointer(System::Runtime::InteropServices::CallingConvention::Cdecl)]
        delegate bool MessageHandler(System::UInt32, System::UIntPtr, System::IntPtr);
        MessageHandler ^ _messageHandler;                                                                                        //!< The delegate handle ( used so that GC doesn't collect the handler ).
        WindowsSubclass * _subclass;                                                                                             //!< The subclass instance.       
        HWND _windowHandle;                                                                                                      //!< Handle of window to be sublassed.

        void RegisterCallback(HWND handle)
        {
            _messageHandler                = gcnew MessageHandler(this, &WindowSubclassCliWrapper::OnMessageReceived);
            System::IntPtr delegatePointer = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_messageHandler);
            _subclass                      = new WindowsSubclass(static_cast<bool(*)(UINT, WPARAM, LPARAM)>(delegatePointer.ToPointer()), handle);
            _subclass->OnSafeSubclass(_windowHandle);
        }

    public:        
        WindowSubclassCliWrapper(IntPtr handle);

        WindowSubclassCliWrapper(HWND handle);

        virtual bool OnMessageReceived(System::UInt32 msg, System::UIntPtr wParam, System::IntPtr lParam) = 0;
        
        ~WindowSubclassCliWrapper();

        bool HasError()
        {
            return _subclass->HasError();
        }

        std::wstring GetLastError()
        {
            return _subclass->LastError();
        }
    };
}
