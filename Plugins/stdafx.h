#include <CommonIncludes.h>

#ifdef __WIN32__
	#include <windows.h>
#elif _MSC_VER
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif
