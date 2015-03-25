#pragma once

#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Endoscopy
	{
		struct ESGUIHintComponentDesc
		{
			Core::IComponent* parent_window = nullptr;
			Core::IComponent* cegui_context = nullptr;
			std::string layout_filename;
			std::string default_text;
			Core::LogSeverity log_level = Core::LogSeverity::NONE;
			
			ESGUIHintComponentDesc():
			default_text("<Endoscopy hint component>")
			{}
		};
	}
}