#pragma once

#include <Properties/Properties_fwd.h>
#include <Descriptors/Components/Lights/OgreDirectionalLightComponentDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreDirectionalLightDescriptorParser
		{
		public:
			static OgreDirectionalLightComponentDescriptor parse(const Core::Properties &props);
		};
	}
}
