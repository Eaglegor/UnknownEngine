#pragma once

#include <Descriptors/OgreRenderSubsystemDescriptor.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
	namespace Graphics
	{
		struct OgreSingleThreadedRenderSubsystemDescriptor
		{
			OgreRenderSubsystemDescriptor base_descriptor;
			Core::IComponent* update_frame_provider;
			
			OgreSingleThreadedRenderSubsystemDescriptor():
			update_frame_provider(nullptr)
			{}			
		};
	}
}