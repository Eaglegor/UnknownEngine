#include <stdafx.h>
#include <Components/PxFixedJointComponent.h>
#include <Components/PxRigidBodyComponent.h>
#include <PhysXSubsystem.h>
#include <Logging.h>

using std::isfinite;

#include <extensions/PxFixedJoint.h>
#include <PxPhysics.h>
#include <PxScene.h>

namespace UnknownEngine
{
	namespace Physics
	{

		PxFixedJointComponent::PxFixedJointComponent(const std::string& name, const PxFixedJointComponentDesc &desc, PhysXSubsystem* physics_subsystem) :
			Core::BaseComponent ( name.c_str() ),
			physics_subsystem(physics_subsystem),
			logger(name.c_str(), desc.log_level),
			desc ( desc ),
			px_joint(nullptr),
			rigid_body1(desc.actor1),
			rigid_body2(desc.actor2)
		{
			Core::ComponentsManager::getSingleton()->reserveComponent(physics_subsystem);
		}

		PxFixedJointComponent::~PxFixedJointComponent()
		{
			Core::ComponentsManager::getSingleton()->releaseComponent(physics_subsystem);
		}

		void PxFixedJointComponent::init()
		{
			if (!rigid_body1 || !rigid_body2){
				LOG_ERROR(logger, "Can't get both actors to create joint");
				throw BothActorsNotFound("Can't get both actors to create joint");
			}
			actor1 = rigid_body1->getPxRigidActor();
			actor2 = rigid_body2->getPxRigidActor();
			
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

	}
}
