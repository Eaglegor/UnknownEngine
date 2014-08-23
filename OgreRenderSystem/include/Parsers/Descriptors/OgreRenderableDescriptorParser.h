#pragma once

#include <Properties/Properties_fwd.h>
#include <Descriptors/Components/Renderables/OgreRenderableComponentDescriptor.h>


namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreRenderableDescriptorParser
		{
			public:
				static OgreRenderableComponentDescriptor parse ( const Core::Properties& properties );
		};

	} // namespace Graphics
} // namespace UnknownEngine
