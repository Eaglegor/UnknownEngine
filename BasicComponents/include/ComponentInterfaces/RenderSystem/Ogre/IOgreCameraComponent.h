#pragma once

#include <ComponentInterfaces/RenderSystem/Common/ICamera.h>

namespace Ogre
{
	class Camera;
}

namespace UnknownEngine
{
	namespace ComponentInterfaces 
	{
		class IOgreCameraComponent : public ICamera
		{
		public:
			constexpr static const char* getTypeName(){return "IOgreCameraComponent";}
			
			virtual Ogre::Camera* getOgreCamera() = 0;
		};
	}
}