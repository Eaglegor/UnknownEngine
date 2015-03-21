#pragma once

#include <ComponentInterfaces/RenderSystem/Common/IRenderable.h>

namespace Ogre
{
	class Renderable;
	class SceneNode;
	class Entity;
}

namespace UnknownEngine
{
	namespace ComponentInterfaces 
	{
		class IOgreRenderableComponent : public IRenderable
		{
		public:
			constexpr static const char* getTypeName(){return "IOgreRenderableComponent";}
			
			virtual Ogre::SceneNode* getSceneNode() = 0;
			virtual Ogre::Entity* getEntity() = 0;
		};
	}
}