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
			
			OgreCEGuiContextDesc():
			render_window(nullptr),
			log_level(Core::LogSeverity::NONE)
			{}
		};
	}
}