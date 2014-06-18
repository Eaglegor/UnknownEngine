#pragma once

#ifdef __MINGW32__
	#define UNKNOWNENGINE_PLUGIN_INTERFACE
#else
	#ifdef BUILDING_SHARED_LIB
		#define UNKNOWNENGINE_PLUGIN_INTERFACE __declspec(dllexport)
	#else
		#define UNKNOWNENGINE_PLUGIN_INTERFACE __declspec(dllimport)
	#endif
#endif
