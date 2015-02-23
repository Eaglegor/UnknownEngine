#pragma once

#include <Properties/Properties_fwd.h>
#include <Descriptors/OgreSeparateThreadRenderSubsystemDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreSeparateThreadRenderSubsystemDescriptorParser
		{
			public:
				static OgreSeparateThreadRenderSubsystemDescriptor parse ( const Core::Properties& properties );
		};

	} // namespace Graphics
} // namespace UnknownEngine
