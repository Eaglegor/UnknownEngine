#pragma once

#include <Properties/Properties_fwd.h>
#include <Descriptors/OgreRenderSubsystemDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreRenderSubsystemDescriptorParser
		{
			public:
				static OgreRenderSubsystemDescriptor parse ( const Core::Properties& properties );
		};

	} // namespace Graphics
} // namespace UnknownEngine
