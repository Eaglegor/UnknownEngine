#pragma once

#include <memory>
#include <Objects/BaseComponent.h>
#include <LogSeverity.h>

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

	namespace Utils
	{
		class LogHelper;
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

			void initializeLogger(Utils::LogSeverity severity);

			PhysXSubsystem* physics_subsystem;
			physx::PxRigidActor* actor1;
			physx::PxRigidActor* actor2;
			Core::EngineContext* engine_context;
			
			std::unique_ptr<Utils::LogHelper> log_helper;

		};
	}
}