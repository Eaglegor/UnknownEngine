#pragma once
#include <LogSeverity.h>
#include <SDLWindowDesc.h>

namespace UnknownEngine
{
	namespace GUI
	{
		struct SDLWindowManagerDescriptor
		{
			Core::LogSeverity log_level = Core::LogSeverity::NONE;
		};
	}
}