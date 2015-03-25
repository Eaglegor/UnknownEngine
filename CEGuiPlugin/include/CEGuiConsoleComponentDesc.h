#pragma once

#include <LogSeverity.h>
#include <string>

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
			Core::IComponent* input_context_mapper;
			std::string game_context_name;
			std::string console_context_name;
			std::string layout_filename;
			
			CEGuiConsoleComponentDesc():
			parent_window(nullptr),
			log_level(Core::LogSeverity::NONE),
			input_context_mapper(nullptr)
			{}
		};
	}
}