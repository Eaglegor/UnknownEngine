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
				DESCRIPTOR_PROPERTY_SETTER(layout_filename);
				DESCRIPTOR_PROPERTY_SETTER(log_level);
				DESCRIPTOR_PROPERTY_SETTER(parent_window);
				DESCRIPTOR_PROPERTY_SETTER(cegui_context);
				DESCRIPTOR_PROPERTY_SETTER(imageset_name);
				DESCRIPTOR_PROPERTY_SETTER(aimed_image_name);
				DESCRIPTOR_PROPERTY_SETTER(free_image_name);
			}
		};
	}
}
