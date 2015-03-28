#pragma once

#include <Descriptors/OgreRenderSubsystemDescriptor.h>
#include <Descriptors/DescriptorUtils.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		struct OgreSingleThreadedRenderSubsystemDescriptor : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			OgreRenderSubsystemDescriptor base_descriptor;
			
			Utils::RequiredComponentDependency update_frame_provider;
			
			OgreSingleThreadedRenderSubsystemDescriptor()
			{
				UEDESC_ADD_NESTED_DESCRIPTOR(base_descriptor);
				UEDESC_ADD_FIELD(update_frame_provider);
			}
		};
	}
}