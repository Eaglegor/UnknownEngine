#pragma once
#include <Components/Lights/OgrePointLightComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class InitialTransformSectionParser
		{
		public:
			static Core::Transform parse(const Core::Properties &props);
		};
	}
}
