#pragma once

#include <string>
#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}

	namespace Endoscopy
	{
		struct ESGUICrosshairComponentDesc
		{
			std::string layout_filename;
			Core::LogSeverity log_level = Core::LogSeverity::NONE;
			Core::IComponent* parent_window = nullptr;
			Core::IComponent* cegui_context = nullptr;
			std::string imageset_name;
			std::string aimed_image_name;
			std::string free_image_name;
		};
	}
}
