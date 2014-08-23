#pragma once

#include <Properties/Properties_fwd.h>
#include <Descriptors/Components/Lights/OgreSpotLightComponentDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreSpotLightDescriptorParser
		{
		public:
			static OgreSpotLightComponentDescriptor parse(const Core::Properties &props);
		};
	}
}
