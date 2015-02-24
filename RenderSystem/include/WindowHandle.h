#pragma once

#include <string>

#ifdef _MSC_VER
	#include <windows.h>
#endif

namespace UnknownEngine
{
	namespace Graphics
	{
#ifdef _MSC_VER
			typedef HWND NativeWindowHandleType;
#else
			typedef unsigned long NativeWindowHandleType;
#endif
			
			static const NativeWindowHandleType INVALID_WINDOW_HANDLE = reinterpret_cast<NativeWindowHandleType>(-1);
	}
}