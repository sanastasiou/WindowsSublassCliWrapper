#include "WindowSubclass.h"

namespace WindowsSubclassWrapper
{
    bool(*WindowsSubclass::_handler)(UINT) = NULL;
}