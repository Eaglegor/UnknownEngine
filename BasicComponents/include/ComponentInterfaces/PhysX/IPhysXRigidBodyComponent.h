#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace physx
{
	class PxRigidActor;
}

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IPhysXRigidBodyComponent : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "IPhysXRigidBodyComponent";}
			
			virtual physx::PxRigidActor* getPxRigidActor() = 0;
		};
	}
}