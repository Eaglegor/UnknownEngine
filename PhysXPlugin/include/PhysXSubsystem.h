#pragma once

#include <InlineSpecification.h>
#include <Exception.h>
#include <memory>

namespace physx
{
	class PxFoundation;
	class PxPhysics;
}

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class LogHelper;
	}

	namespace Physics
	{
		class PhysXSubsystem
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(PhysXInitFailed);

			PhysXSubsystem(Core::EngineContext* engine_context, Core::LogHelper* log_helper);
			~PhysXSubsystem();

			UNKNOWNENGINE_INLINE
			bool isInitialized(){ return is_initialized; }

		private:
			bool is_initialized;

			Core::EngineContext* engine_context;
			Core::LogHelper* log_helper;

			physx::PxFoundation* px_foundation;
			physx::PxPhysics* px_physics;
		};
	}
}