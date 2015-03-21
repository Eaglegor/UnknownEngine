#pragma once

#include <LogSeverity.h>
#include <cstdint>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		struct OgreHOQVisibilityCheckerDesc
		{
			Core::IComponent* checkable_object;
			Core::IComponent* render_window;
			Core::LogSeverity log_level;
			uint8_t render_queue_group;
			
			OgreHOQVisibilityCheckerDesc():
			checkable_object(nullptr),
			render_window(nullptr),
			log_level(Core::LogSeverity::NONE),
			render_queue_group(51)
			{}
		};
	}
}