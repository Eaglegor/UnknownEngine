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
		struct CEGuiConsoleComponentDesc
		{
			Core::IComponent* parent_window;
			Core::LogSeverity log_level;
			
			CEGuiConsoleComponentDesc():
			parent_window(nullptr),
			log_level(Core::LogSeverity::NONE)
			{}
		};
	}
}