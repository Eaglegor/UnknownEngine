#pragma once

#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace GUI
	{
		struct FrameWindowDesc
		{
			Core::IComponent* parent_window;
			Core::LogSeverity log_level;
			std::string window_type;
			std::string window_caption;
			
			FrameWindowDesc():
			parent_window(nullptr),
			log_level(Core::LogSeverity::NONE)
			{}
		};
	}
}