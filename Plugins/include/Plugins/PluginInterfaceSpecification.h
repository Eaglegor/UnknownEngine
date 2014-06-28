#pragma once

#ifdef _MSC_VER
	#ifdef BUILDING_SHARED_LIB
		#define UNKNOWNENGINE_PLUGIN_INTERFACE __declspec(dllexport)
	#else
		#define UNKNOWNENGINE_PLUGIN_INTERFACE __declspec(dllimport)
	#endif
#else
	#define UNKNOWNENGINE_PLUGIN_INTERFACE
#endif
