#pragma once

#include <Quaternion.h>
#include <OgreQuaternion.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreQuaternionConverter
		{
			public:
				static Ogre::Quaternion toOgreQuaternion ( const Math::Quaternion& quat )
				{
					return Ogre::Quaternion ( quat.w(), quat.x(), quat.y(), quat.z() );
				}
				static Math::Quaternion fromOgreQuaternion ( const Ogre::Quaternion& quat )
				{
					return Math::Quaternion ( quat.x, quat.y, quat.z, quat.w );
				}
		};
	}
}