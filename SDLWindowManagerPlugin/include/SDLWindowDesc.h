#pragma once

#include <string>
#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace GUI
	{
		
		struct SDLWindowDesc
		{
			std::string window_title;
			size_t width;
			size_t height;
			
			bool resizable;
			bool full_screen;
			
			Core::LogSeverity log_level = Core::LogSeverity::NONE;
			
			Core::IComponent* update_frame_provider;
		};
		
	}
}