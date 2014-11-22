#pragma once
#include <BaseComponentFactory.h>

namespace UnknownEngine
{
	
	namespace Core
	{
		class EngineContext;
	}
	
	namespace Physics
	{
		class PhysXSubsystem;

		class PxRigidBodyComponentsFactory : public Core::BaseComponentFactory
		{
		public:
			PxRigidBodyComponentsFactory( PhysXSubsystem* physx_subsystem, Core::EngineContext* engine_context );
			
		private:
			Core::IComponent* createPxRigidBodyComponent(const Core::ComponentDesc& desc);
			
			virtual const char* getName() const override;
			
			PhysXSubsystem* physx_subsystem;
			Core::EngineContext* engine_context;
			
		};
	}
}