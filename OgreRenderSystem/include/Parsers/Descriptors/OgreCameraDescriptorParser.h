#pragma once

#include <Properties/Properties_fwd.h>
#include <Components/Cameras/OgreCameraComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreCameraDescriptorParser
		{
			public:
				static OgreCameraComponentDescriptor parse ( const Core::Properties& properties );
		};

	} // namespace Graphics
} // namespace UnknownEngine
