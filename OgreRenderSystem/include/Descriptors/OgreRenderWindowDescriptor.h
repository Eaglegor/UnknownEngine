#pragma once

#include <LogSeverity.h>
#include <Descriptors/DescriptorUtils.h>
#include <Descriptors/OgreRenderWindowType.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		struct OgreRenderWindowDescriptor : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			Utils::OptionalProperty<std::string> window_title;
			Utils::OptionalProperty<size_t> width;
			Utils::OptionalProperty<size_t> height;
			Utils::OptionalProperty<OgreRenderWindowType> type;
			
			Utils::OptionalComponentDependency parent_window;
			
			Utils::OptionalProperty<bool> fullscreen;
			
			Utils::OptionalProperty<Core::LogSeverity> log_level;
			
			OgreRenderWindowDescriptor():
			width(640),
			height(480),
			type(OgreRenderWindowType::OWN),
			fullscreen(false),
			log_level(Core::LogSeverity::NONE)
			{
				UEDESC_ADD_FIELD(window_title);
				UEDESC_ADD_FIELD(width);
				UEDESC_ADD_FIELD(height);
				UEDESC_ADD_FIELD(type);
				UEDESC_ADD_FIELD(fullscreen);
				UEDESC_ADD_FIELD(parent_window);
				UEDESC_ADD_FIELD(log_level);
			}
		};
	}
}