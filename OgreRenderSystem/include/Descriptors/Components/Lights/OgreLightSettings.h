#pragma once

#include <Scalar.h>
#include <boost/optional.hpp>
#include <OgreColourValue.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		struct OgreLightSettings
		{
			struct Attenuation
			{
				Math::Scalar range;
				Math::Scalar constant;
				Math::Scalar linear;
				Math::Scalar quadratic;
			};

			boost::optional<Attenuation> attenuation;
			boost::optional<bool> cast_shadows;

			Ogre::ColourValue diffuse_color;
			Ogre::ColourValue specular_color;
			Math::Scalar intensity;

			OgreLightSettings() :
				diffuse_color ( 1, 1, 1 ),
				specular_color ( 1, 1, 1 ),
				intensity ( 1 )
			{}

		};
	}
}
