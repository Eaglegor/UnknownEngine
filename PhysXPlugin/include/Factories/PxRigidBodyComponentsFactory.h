#pragma once
#include <BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace Physics
	{
		class PhysXSubsystem;

		class PxRigidBodyComponentsFactory : public Core::BaseComponentFactory
		{
		public:
			PxRigidBodyComponentsFactory(PhysXSubsystem *physx_subsystem);
			
		private:
			Core::IComponent* createPxRigidBodyComponent(const Core::ComponentDesc& desc);
			
			virtual const char* getName();
			
			PhysXSubsystem* physx_subsystem;
			
		};
	}
}