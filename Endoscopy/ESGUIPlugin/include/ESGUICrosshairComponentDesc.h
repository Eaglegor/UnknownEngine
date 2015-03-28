#pragma once

#include <string>
#include <LogSeverity.h>
#include <Descriptors/DescriptorUtils.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}

	namespace Endoscopy
	{
		struct ESGUICrosshairComponentDesc : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			Utils::RequiredProperty<std::string> layout_filename;
			Utils::OptionalProperty<Core::LogSeverity> log_level;
			Utils::RequiredComponentDependency parent_window;
			Utils::RequiredComponentDependency cegui_context;
			Utils::RequiredProperty<std::string> imageset_name;
			Utils::RequiredProperty<std::string> aimed_image_name;
			Utils::RequiredProperty<std::string> free_image_name;

			ESGUICrosshairComponentDesc():
			log_level(Core::LogSeverity::NONE)
			{
				UEDESC_ADD_FIELD(layout_filename);
				UEDESC_ADD_FIELD(log_level);
				UEDESC_ADD_FIELD(parent_window);
				UEDESC_ADD_FIELD(cegui_context);
				UEDESC_ADD_FIELD(imageset_name);
				UEDESC_ADD_FIELD(aimed_image_name);
				UEDESC_ADD_FIELD(free_image_name);
			}
		};
	}
}
