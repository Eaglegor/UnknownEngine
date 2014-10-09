#include <PhysXSubsystem.h>
#include <PxPhysicsAPI.h>
#include <LogHelper.h>

static physx::PxDefaultErrorCallback gDefaultErrorCallback;
static physx::PxDefaultAllocator gDefaultAllocatorCallback;

namespace UnknownEngine
{
	namespace Physics
	{
		PhysXSubsystem::PhysXSubsystem(Core::EngineContext* engine_context, Core::LogHelper* log_helper):
			is_initialized(false),
			engine_context(engine_context),
			log_helper(log_helper)
		{
			px_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
			if (px_foundation == nullptr)
			{
				LOG_ERROR(log_helper, "Failed to create PxFoundation class. PhysX not initialized");
			}
			else
			{
				px_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *px_foundation, physx::PxTolerancesScale());
				if (px_physics == nullptr)
				{
					LOG_ERROR(log_helper, "Failed to initialize PxPhysics class. PhysX not initialized");
				}
				else
				{
					is_initialized = true;
				}
			}
		}

		PhysXSubsystem::~PhysXSubsystem()
		{
			if (px_physics) px_physics->release();
			if (px_foundation) px_foundation->release();
		}

	}
}