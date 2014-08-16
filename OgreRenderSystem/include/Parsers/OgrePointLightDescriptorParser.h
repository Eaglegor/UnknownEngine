#pragma once
#include <Components/OgrePointLightComponent.h>

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
