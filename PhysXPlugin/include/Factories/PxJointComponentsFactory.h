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

		class PxJointComponentsFactory : public Core::BaseComponentFactory
		{
		public:
			PxJointComponentsFactory( PhysXSubsystem* physx_subsystem, Core::EngineContext* engine_context );
			
		private:
			Core::IComponent* createPxFixedJointComponent(const Core::ComponentDesc& desc);
			
			virtual const char* getName();
			
			PhysXSubsystem* physx_subsystem;
			Core::EngineContext* engine_context;
			
		};
	}
}