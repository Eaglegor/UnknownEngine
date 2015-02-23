#pragma once

#include <Properties/Properties_fwd.h>
#include <Descriptors/OgreSingleThreadedRenderSubsystemDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreSingleThreadedRenderSubsystemDescriptorParser
		{
			public:
				static OgreSingleThreadedRenderSubsystemDescriptor parse ( const Core::Properties& properties );
		};

	} // namespace Graphics
} // namespace UnknownEngine
