#pragma once

#include <string>

#ifdef _MSC_VER
	#include <windows.h>
#endif

namespace UnknownEngine
{
	namespace Graphics
	{
		class WindowHandle
		{
		public:
#ifdef _MSC_VER
			typedef HWND NativeWindowHandleType;
#else
			typedef size_t NativeWindowHandleType;
#endif
			
			WindowHandle(NativeWindowHandleType handle):handle(handle){}
			WindowHandle(){}
			
			void setUnsignedHandle(size_t handle) {this->handle = static_cast<NativeWindowHandleType>(handle);}
			size_t getUnsignedHandle(){return static_cast<size_t>(handle);}
			
			void setVoidHandle(const void* handle){this->handle = *(static_cast<const NativeWindowHandleType*>(handle));}
			const void* getVoidHandle(){return static_cast<void*>(&handle);}
			
			void setNativeHandle(NativeWindowHandleType handle){this->handle = handle;}
			NativeWindowHandleType getNativeHandle(){return handle;}
			
			
		private:
			NativeWindowHandleType handle;
		};
	}
}