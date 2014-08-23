#pragma once

#include <InlineSpecification.h>
#include <Vectors/Vector3.h>
#include <Vectors/Vector4.h>
#include <OgreColourValue.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreColourValueConverter
		{
			public:
				static Ogre::ColourValue toOgreColourValue ( const Math::Vector3& vector )
				{
					return Ogre::ColourValue ( vector.x(), vector.y(), vector.z() );
				}
				static Ogre::ColourValue toOgreColourValue ( const Math::Vector4& vector )
				{
					return Ogre::ColourValue ( vector.x(), vector.y(), vector.z(), vector.w() );
				}
				
				static Math::Vector3 fromOgreColourValueToVector3 ( const Ogre::ColourValue& color )
				{
					return Math::Vector3 ( color.r, color.g, color.b );
				}
				static Math::Vector4 fromOgreColourValueToVector4 ( const Ogre::ColourValue& color )
				{
					return Math::Vector4 ( color.r, color.g, color.b, color.a );
				}
		};
	}
}
