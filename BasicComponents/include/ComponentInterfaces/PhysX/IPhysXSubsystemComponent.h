#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace physx
{
	class PxPhysics;
	class PxScene;
}

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IPhysXSubsystemComponent : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getTypeName(){return "IPhysXSubsystemComponent";}
			
			virtual physx::PxPhysics* getPxPhysics() = 0;
			virtual physx::PxScene* getPxScene() = 0;
		};
	}
}