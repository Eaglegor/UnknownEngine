#include <stdafx.h>
#include <Components/PxFixedJointComponent.h>
#include <Components/PxRigidBodyComponent.h>
#include <PhysXSubsystem.h>
#include <LogHelper.h>

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
			physx::PxTransform relative_transform_1, relative_transform_2;
			calculateRelativeTransforms(relative_transform_1, relative_transform_2);
			px_joint = physx::PxFixedJointCreate(*physics_subsystem->getPxPhysics(), actor1, relative_transform_1, actor2, relative_transform_2);

			if (desc.use_projection)
			{
				px_joint->setConstraintFlag(physx::PxConstraintFlag::ePROJECTION, true);
				if (desc.projection_angular_tolerance) px_joint->setProjectionAngularTolerance(desc.projection_angular_tolerance.get());
				if (desc.projection_linear_tolerance) px_joint->setProjectionLinearTolerance(desc.projection_linear_tolerance.get());
			}
			
			px_joint->setConstraintFlag(physx::PxConstraintFlag::eCOLLISION_ENABLED, desc.collision_enabled);

		}

		void PxFixedJointComponent::calculateRelativeTransforms(physx::PxTransform &rel_transform_1, physx::PxTransform &rel_transform_2)
		{
			rel_transform_1 = physx::PxTransform::createIdentity();
			rel_transform_2 = actor2->getGlobalPose().getInverse() * actor1->getGlobalPose();
		}

		void PxFixedJointComponent::shutdown()
		{
			px_joint->release();
		}

		Core::ComponentType PxFixedJointComponent::getType() const
		{
			return PX_FIXED_JOINT_COMPONENT_TYPE;
		}

	}
}
