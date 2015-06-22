#pragma once

#include <ResourceManager/ResourceTypeMetaInfo.h>
#include <OgreMesh.h>

namespace UnknownEngine
{
	namespace Resources
	{
		template<>
		class ResourceTypeMetaInfo<Ogre::Mesh*> : public IResourceTypeMetaInfo
		{
		public:
			virtual ResourceType getType() { return staticGetType(); }
			virtual ResourceType staticGetType() { return "Ogre.Mesh"; }
		};
	}
}
