#pragma once

#include <LogSeverity.h>
#include <cstdint>
#include <Descriptors/DescriptorUtils.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		struct OgreHOQVisibilityCheckerDesc : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			Utils::RequiredComponentDependency checkable_object;
			Utils::RequiredComponentDependency render_window;
			
			Utils::OptionalProperty<Core::LogSeverity> log_level;
			Utils::OptionalProperty<uint8_t> render_queue_group;
			
			OgreHOQVisibilityCheckerDesc():
			log_level(Core::LogSeverity::NONE),
			render_queue_group(51)
			{
				UEDESC_ADD_FIELD(checkable_object);
				UEDESC_ADD_FIELD(render_window);
				UEDESC_ADD_FIELD(log_level);
				UEDESC_ADD_FIELD(render_queue_group);
			}
		};
	}
}