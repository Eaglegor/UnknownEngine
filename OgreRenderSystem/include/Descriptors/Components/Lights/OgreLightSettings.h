#pragma once

#include <Scalar.h>
#include <boost/optional.hpp>
#include <OgreColourValue.h>
#include <AlignedNew.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		UNKNOWNENGINE_ALIGNED_STRUCT(16) OgreLightSettings
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

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			OgreLightSettings() :
				diffuse_color ( 1, 1, 1 ),
				specular_color ( 1, 1, 1 ),
				intensity ( 1 )
			{}

		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreLightSettings);