#pragma once

#include <ResourceManager/ResourceTypeMetaInfo.h>
#include <OgreMaterial.h>

namespace UnknownEngine
{
	namespace Resources
	{
		template<>
		class ResourceTypeMetaInfo<Ogre::Material*> : public IResourceTypeMetaInfo
		{
		public:
			virtual ResourceType getType() { return staticGetType(); }
			virtual ResourceType staticGetType() { return "Ogre.Material"; }
		};
	}
}
