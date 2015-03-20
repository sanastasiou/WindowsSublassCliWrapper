========================================================================
    STATIC LIBRARY : WindowsSubclassCliWrapper Project Overview
========================================================================

This simple library is used as a cli wrapper, so that a .net application can easily
sublcass a win32 window and override it's WndProc event without having to resort to countless
PInvoke calls.

The library takes care of unsubclassing from the window, in case the window is destroyed and upon 
destruction of the relevant objects.

Clients of this library can subscribe to the normal windows messages of the window they are subclassing.

The window to be sublassed and the .net application have to belong to the same process.