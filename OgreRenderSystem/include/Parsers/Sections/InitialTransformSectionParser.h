#pragma once
#include <Components/Lights/OgrePointLightComponent.h>
#include <Properties/Properties.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class InitialTransformSectionParser
		{
		public:
			static Math::Transform parse(const Core::Properties &props);
		};
	}
}
