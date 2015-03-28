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
				UEDESC_ADD_FIELD(parent_window);
				UEDESC_ADD_FIELD(cegui_context);
				UEDESC_ADD_FIELD(layout_filename);
				UEDESC_ADD_FIELD(default_text);
				UEDESC_ADD_FIELD(log_level);
			}
		};
	}
}