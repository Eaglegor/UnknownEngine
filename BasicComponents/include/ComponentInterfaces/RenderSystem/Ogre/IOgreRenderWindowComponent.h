#pragma once

#include <OgreRenderWindow.h>
#include <ComponentInterfaces/RenderSystem/IRenderWindowComponent.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IOgreRenderWindowComponent : public IRenderWindowComponent
		{
		public:
			constexpr static const char* getType(){return "IOgreRenderWindowComponent";}
			
			virtual Ogre::RenderWindow* getOgreRenderWindow() = 0;
		};
	}
}