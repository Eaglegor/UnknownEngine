#pragma once

#include <Components/OgreRenderableComponent.h>
#include <Properties/Properties.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreRenderableDescriptorParser
		{
			public:
				static OgreRenderableComponent::Descriptor parse ( const Core::Properties& properties );
		};

	} // namespace Graphics
} // namespace UnknownEngine
