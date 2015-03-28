#pragma once

#include <Descriptors/OgreRenderSubsystemDescriptor.h>
#include <Descriptors/DescriptorUtils.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		struct OgreSeparateThreadRenderSubsystemDescriptor : public Utils::Descriptor
		{
			using Utils::Descriptor::operator=;
			
			OgreRenderSubsystemDescriptor base_descriptor;
			
			OgreSeparateThreadRenderSubsystemDescriptor()
			{
				UEDESC_ADD_NESTED_DESCRIPTOR(base_descriptor);
			}
		};
	}
}