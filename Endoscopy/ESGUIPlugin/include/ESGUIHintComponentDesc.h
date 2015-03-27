#pragma once

#include <LogSeverity.h>
#include <Logging.h>
#include <Descriptors/DescriptorUtils.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Endoscopy
	{
		struct ESGUIHintComponentDesc : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			Utils::RequiredComponentDependency parent_window;
			Utils::RequiredComponentDependency cegui_context;
			Utils::RequiredProperty<std::string> layout_filename;
			Utils::OptionalProperty<std::string> default_text;
			Utils::OptionalProperty<Core::LogSeverity> log_level;
			
			ESGUIHintComponentDesc():
			default_text("<Endoscopy hint component>"),
			log_level(Core::LogSeverity::NONE)
			{
				DESCRIPTOR_PROPERTY_SETTER(parent_window);
				DESCRIPTOR_PROPERTY_SETTER(cegui_context);
				DESCRIPTOR_PROPERTY_SETTER(layout_filename);
				DESCRIPTOR_PROPERTY_SETTER(default_text);
				DESCRIPTOR_PROPERTY_SETTER(log_level);
			}
		};
	}
}