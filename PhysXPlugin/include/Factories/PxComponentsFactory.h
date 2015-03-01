#pragma once
#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace Physics
	{
		class PhysXSubsystem;

		class PxComponentsFactory : public Core::BaseComponentFactory
		{
		public:
			PxComponentsFactory();

			virtual const char* getName() const override {return "PhysX.ComponentsFactory";}			
			
			void setPhysXSubsystem(PhysXSubsystem* physx_subsystem);
		private:
			Core::IComponent* createPxRigidBodyComponent(const Core::ComponentDesc& desc);
			
			Core::IComponent* createPxFixedJointComponent(const Core::ComponentDesc& desc);
			
			
			
			PhysXSubsystem* physx_subsystem;
		};
	}
}