#include "WindowSubclassCliWrapper.h"

namespace WindowsSubclassWrapper
{
    WindowSubclassCliWrapper::WindowSubclassCliWrapper(IntPtr handle)
    {
        _windowHandle = (HWND)(handle.ToPointer());
        RegisterCallback(_windowHandle);
    }

    WindowSubclassCliWrapper::WindowSubclassCliWrapper(HWND handle) : _windowHandle(handle)
    {
        RegisterCallback(_windowHandle);
    }

    WindowSubclassCliWrapper::~WindowSubclassCliWrapper()
    {
        delete _subclass;
    }

}
