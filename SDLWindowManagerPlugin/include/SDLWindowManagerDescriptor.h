#pragma once
#include <LogSeverity.h>
#include <SDLWindowDesc.h>

namespace UnknownEngine
{
	namespace GUI
	{
		struct SDLWindowManagerDescriptor
		{
			SDLWindowDesc window_desc;
			Utils::LogSeverity log_level;

			SDLWindowManagerDescriptor() :
				log_level(Utils::LogSeverity::NONE)
			{}
		};
	}
}