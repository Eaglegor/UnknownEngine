#pragma once
#include <Components/Lights/OgreSpotLightComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreSpotLightDescriptorParser
		{
		public:
			static OgreSpotLightComponent::Descriptor parse(const Core::Properties &props);
		};
	}
}
