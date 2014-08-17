#pragma once
#include <Components/Lights/OgreDirectionalLightComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreDirectionalLightDescriptorParser
		{
		public:
			static OgreDirectionalLightComponent::Descriptor parse(const Core::Properties &props);
		};
	}
}
