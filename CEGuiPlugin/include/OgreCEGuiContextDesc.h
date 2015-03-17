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
		struct OgreCEGuiContextDesc
		{
			Core::IComponent* render_window;
			Core::LogSeverity log_level;
			
			Core::IComponent* keyboard_handler;
			Core::IComponent* mouse_handler;
			
			OgreCEGuiContextDesc():
			render_window(nullptr),
			log_level(Core::LogSeverity::NONE),
			keyboard_handler(nullptr),
			mouse_handler(nullptr)
			{}
		};
	}
}