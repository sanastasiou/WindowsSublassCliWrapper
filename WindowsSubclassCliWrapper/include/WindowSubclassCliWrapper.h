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
        delegate bool MessageHandler(UINT message);
        MessageHandler ^ _messageHandler;           //!< The delegate handle ( used so that GC doesn't collect the handler ).
        WindowsSubclass * _subclass;                //!< The subclass instance.       
        HWND _windowHandle;

        void RegisterCallback(HWND handle)
        {
            _messageHandler                = gcnew MessageHandler(this, &WindowSubclassCliWrapper::OnMessageReceived);
            System::IntPtr delegatePointer = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_messageHandler);
            _subclass                      = new WindowsSubclass(static_cast<bool(*)(UINT)>(delegatePointer.ToPointer()), handle);
            _subclass->OnSafeSubclass(_windowHandle);
        }

    public:        
        WindowSubclassCliWrapper(IntPtr handle);

        WindowSubclassCliWrapper(HWND handle);

        virtual bool OnMessageReceived(UINT message) = 0;
        
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
