#pragma once
#include <Components/Lights/OgrePointLightComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgrePointLightDescriptorParser
		{
		public:
			static OgrePointLightComponent::Descriptor parse(const Core::Properties &props);
		};
	}
}
