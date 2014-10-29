#include <Components/PxFixedJointComponent.h>
#include <Components/PxRigidBodyComponent.h>
#include <PhysXSubsystem.h>

using std::isfinite;

#include <extensions/PxFixedJoint.h>
#include <PxPhysics.h>
#include <PxScene.h>

namespace UnknownEngine
{
	namespace Physics
	{

		PxFixedJointComponent::PxFixedJointComponent(const std::string& name, const PxFixedJointComponentDesc &desc, PhysXSubsystem* physics_subsystem, Core::EngineContext* engine_context) :
			PxJointComponent ( name, physics_subsystem, engine_context ),
			desc ( desc ),
			px_joint(nullptr)
		{
		}

		PxFixedJointComponent::~PxFixedJointComponent()
		{
		}

		void PxFixedJointComponent::init(const Core::Entity* parent_entity)
		{
			actor1 = physics_subsystem->getRigidBodyComponent(desc.actor1_name)->getPxRigidActor();
			actor2 = physics_subsystem->getRigidBodyComponent(desc.actor2_name)->getPxRigidActor();
			if (actor1 == nullptr || actor2 == nullptr){
				LOG_ERROR(log_helper, "Can't get both actors to create joint");
				throw BothActorsNotFound("Can't get both actors to create joint");
			}
			px_joint = physx::PxFixedJointCreate(*physics_subsystem->getPxPhysics(), actor1, physx::PxTransform::createIdentity(), actor2, physx::PxTransform::createIdentity());
		}

		void PxFixedJointComponent::shutdown()
		{
			px_joint->release();
		}

		Core::ComponentType PxFixedJointComponent::getType()
		{
			return PX_FIXED_JOINT_COMPONENT_TYPE;
		}

	}
}
