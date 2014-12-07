#pragma once

#include <memory>
#include <ComponentSystem/BaseComponent.h>
#include <LogSeverity.h>
#include <LogHelper.h>

namespace physx
{
	class PxRigidActor;
	class PxFixedJoint;
}

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
	}

	namespace Physics
	{

		class PhysXSubsystem;
		
		class PxJointComponent : public Core::BaseComponent
		{
		public:
			PxJointComponent(const std::string & name, UnknownEngine::Physics::PhysXSubsystem * physics_subsystem, Core::EngineContext * engine_context);
			virtual ~PxJointComponent();

		protected:

			void initializeLogger(Core::LogSeverity severity);

			PhysXSubsystem* physics_subsystem;
			physx::PxRigidActor* actor1;
			physx::PxRigidActor* actor2;
			Core::EngineContext* engine_context;
			
			Core::LogHelper logger;
		};
	}
}