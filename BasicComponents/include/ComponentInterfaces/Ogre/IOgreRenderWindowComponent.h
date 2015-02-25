#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <OgreRenderWindow.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IOgreRenderWindowComponent : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getTypeName(){return "OgreRenderWindowComponent";}
			
			virtual Ogre::RenderWindow* getOgreRenderWindow() = 0;
		};
	}
}