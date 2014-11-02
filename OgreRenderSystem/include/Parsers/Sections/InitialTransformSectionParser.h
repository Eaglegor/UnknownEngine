#pragma once
#include <Components/Lights/OgrePointLightComponent.h>

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
