#include <stdafx.h>
#include <Components/PxRigidBodyComponent.h>
#include <Components/PxShapeOrientedWrapper.h>
#include <PhysXSubsystem.h>

#include <Converters/PxTransformConverter.h>
#include <DataProviders/PxShapeDataProvider.h>

#include <Logging.h>

#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <MessageSystem/BaseMessageListener.h>

using std::isfinite;

#include <PxRigidDynamic.h>
#include <PxRigidStatic.h>
#include <PxPhysics.h>
#include <PxScene.h>
#include <ResourceManager/ResourceManager.h>

namespace UnknownEngine
{
	namespace Physics
	{

		PxRigidBodyComponent::PxRigidBodyComponent ( const std::string& name, const PxRigidBodyComponentDesc &desc, PhysXSubsystem* physics_subsystem) :
			Core::BaseComponent ( name.c_str() ),
			transform_message_sender(name),
			desc ( desc ),
			physics_subsystem ( physics_subsystem ),
			px_rigid_body ( nullptr ),
			px_shape ( nullptr ),
			first_update_passed(false)
		{
			Core::ComponentsManager::getSingleton()->reserveComponent(physics_subsystem);
			GET_DATA_PROVIDER(desc.shape_data_provider->getName());
		}

		PxRigidBodyComponent::~PxRigidBodyComponent()
		{
			RELEASE_DATA_PROVIDER(desc.shape_data_provider);
			Core::ComponentsManager::getSingleton()->releaseComponent(physics_subsystem);
		}

		void PxRigidBodyComponent::init()
		{
			switch (desc.dynamics_type)
			{
			case RigidBodyDynamicsType::DYNAMIC:
			case RigidBodyDynamicsType::KINEMATIC:
			{
				px_rigid_body = physics_subsystem->getPxPhysics()->createRigidDynamic(PxTransformConverter::toPxTransform(desc.initial_transform));

				physx::PxRigidDynamic* dynamic_rigid = px_rigid_body->isRigidDynamic();
				if (dynamic_rigid)
				{
					if (desc.dynamics_type == RigidBodyDynamicsType::KINEMATIC)
					{
						dynamic_rigid->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);
					}

					if (desc.linear_damping) dynamic_rigid->setLinearDamping(desc.linear_damping.get());
					if (desc.angular_damping) dynamic_rigid->setAngularDamping(desc.angular_damping.get());
					if (desc.max_angular_velocity) dynamic_rigid->setMaxAngularVelocity(desc.max_angular_velocity.get());
					if (desc.stabilization_threshold) dynamic_rigid->setStabilizationThreshold(desc.stabilization_threshold.get());
					if (desc.position_iterations) dynamic_rigid->setSolverIterationCounts(desc.position_iterations.get(), desc.velocity_iterations ? desc.velocity_iterations.get() : 1);
					if (desc.contact_report_threshold) dynamic_rigid->setContactReportThreshold(desc.contact_report_threshold.get());
				}

				break;
			}
			case RigidBodyDynamicsType::STATIC:
			{
				px_rigid_body = physics_subsystem->getPxPhysics()->createRigidStatic(PxTransformConverter::toPxTransform(desc.initial_transform));
				break;
			}
			}

			px_shape = desc.shape_data_provider->getPxShapeWrapper();

			px_rigid_body->attachShape(*px_shape->getPxShape());
			if (px_shape->getPxShape()->isExclusive())
			{
				px_shape->setLocalPose(desc.local_shape_transform);
			}

			physics_subsystem->getPxScene()->addActor ( *px_rigid_body );
			
			physics_subsystem->addUpdateListener(this);
		}

		void PxRigidBodyComponent::update()
		{
			physx::PxRigidDynamic* dynamic_rigid = px_rigid_body->isRigidDynamic();
			if(!first_update_passed || (dynamic_rigid && !dynamic_rigid->isSleeping()))
			{
				current_transform = PxTransformConverter::fromPxTransform(px_rigid_body->getGlobalPose());
				if(!first_update_passed) first_update_passed = true;
			}
		}
		
		void PxRigidBodyComponent::shutdown()
		{
			physics_subsystem->removeUpdateListener(this);
			physics_subsystem->getPxScene()->removeActor ( *px_rigid_body );
			px_rigid_body->release();
		}
		
		void PxRigidBodyComponent::setTransform(const Math::Transform &transform)
		{
			physx::PxRigidDynamic* dynamic_rigid = px_rigid_body->isRigidDynamic();
			if (dynamic_rigid) {
				switch (desc.dynamics_type)
				{
					case RigidBodyDynamicsType::KINEMATIC:
					{
						dynamic_rigid->setKinematicTarget(PxTransformConverter::toPxTransform(transform));
						break;
					}
					case RigidBodyDynamicsType::DYNAMIC:
					{
						dynamic_rigid->setGlobalPose(PxTransformConverter::toPxTransform(transform));
						break;
					}
				}
			}
		}

		Math::Quaternion PxRigidBodyComponent::getOrientation()
		{
			return current_transform.getOrientation();
		}

		Math::Vector3 PxRigidBodyComponent::getPosition()
		{
			return current_transform.getPosition();
		}

		Math::Transform PxRigidBodyComponent::getTransform()
		{
			return current_transform;
		}
		
		Core::IComponentInterface* PxRigidBodyComponent::getInterface ( const Core::ComponentType& type )
		{
			if(type == ComponentInterfaces::IPhysXRigidBodyComponent::getTypeName()) return static_cast<ComponentInterfaces::IPhysXRigidBodyComponent*>(this);
			if(type == ComponentInterfaces::TransformHolderComponent::getTypeName()) return static_cast<ComponentInterfaces::TransformHolderComponent*>(this);
			return nullptr;
		}
		
	}
}
