#pragma once

#include <Properties/Properties_fwd.h>
#include <Descriptors/Components/Lights/OgrePointLightComponentDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgrePointLightDescriptorParser
		{
		public:
			static OgrePointLightComponentDescriptor parse(const Core::Properties &props);
		};
	}
}
