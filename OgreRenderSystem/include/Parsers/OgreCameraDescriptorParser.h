#pragma once

#include <Components/OgreCameraComponent.h>
#include <Properties/Properties.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreCameraDescriptorParser
		{
			public:
				static OgreCameraComponent::Descriptor parse ( const Core::Properties& properties );
		};

	} // namespace Graphics
} // namespace UnknownEngine
