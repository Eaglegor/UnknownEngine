#include <Components/PxRigidBodyComponent.h>
#include <Components/PxShapeOrientedWrapper.h>
#include <PhysXSubsystem.h>

#include <Converters/PxTransformConverter.h>
#include <DataProviders/PxShapeDataProvider.h>

using std::isfinite;

#include <PxRigidDynamic.h>
#include <PxRigidStatic.h>
#include <PxPhysics.h>
#include <PxScene.h>

namespace UnknownEngine
{
	namespace Physics
	{

		PxRigidBodyComponent::PxRigidBodyComponent ( const std::string& name, const PxRigidBodyComponentDesc &desc, PhysXSubsystem* physics_subsystem, Core::EngineContext* engine_context ) :
			Core::BaseComponent ( name ),
			desc ( desc ),
			physics_subsystem ( physics_subsystem ),
			px_rigid_body ( nullptr ),
			px_shape ( nullptr ),
			transform_message_sender(GET_OR_CREATE_MESSAGE_SYSTEM_PARTICIPANT_ID(name), engine_context )
		{
			desc.shape_data_provider->reserve();
		}

		PxRigidBodyComponent::~PxRigidBodyComponent()
		{
			desc.shape_data_provider->release();
		}

		void PxRigidBodyComponent::init ( const Core::Entity* parent_entity )
		{
			switch ( desc.dynamics_type )
			{
			case RigidBodyDynamicsType::DYNAMIC:
			case RigidBodyDynamicsType::KINEMATIC:
				{
					px_rigid_body = physics_subsystem->getPxPhysics()->createRigidDynamic ( PxTransformConverter::toPxTransform ( desc.initial_transform ) );

					physx::PxRigidDynamic* dynamic_rigid = px_rigid_body->isRigidDynamic();
					if ( dynamic_rigid )
					{
						if ( desc.dynamics_type == RigidBodyDynamicsType::KINEMATIC )
						{
							dynamic_rigid->setRigidBodyFlag ( physx::PxRigidBodyFlag::eKINEMATIC, true );
						}
						
						if ( desc.linear_damping ) dynamic_rigid->setLinearDamping ( desc.linear_damping.get() );
						if ( desc.angular_damping ) dynamic_rigid->setAngularDamping ( desc.angular_damping.get() );
						if ( desc.max_angular_velocity ) dynamic_rigid->setMaxAngularVelocity ( desc.max_angular_velocity.get() );
						if ( desc.stabilization_threshold ) dynamic_rigid->setStabilizationThreshold ( desc.stabilization_threshold.get() );
						if ( desc.position_iterations ) dynamic_rigid->setSolverIterationCounts ( desc.position_iterations.get(), desc.velocity_iterations ? desc.velocity_iterations.get() : 1 );
						if ( desc.contact_report_threshold ) dynamic_rigid->setContactReportThreshold ( desc.contact_report_threshold.get() );
					}

					break;
				}
			case RigidBodyDynamicsType::STATIC:
				{
					px_rigid_body = physics_subsystem->getPxPhysics()->createRigidStatic ( PxTransformConverter::toPxTransform ( desc.initial_transform ) );
					break;
				}
			}

			px_shape = desc.shape_data_provider->getPxShapeWrapper();

			px_rigid_body->attachShape ( *px_shape->getPxShape() );
			px_shape->setLocalPose ( desc.local_shape_transform );

			physics_subsystem->getPxScene()->addActor ( *px_rigid_body );
			physics_subsystem->addRigidBodyComponent(getName(), this);

		}

		void PxRigidBodyComponent::update()
		{
			physx::PxRigidDynamic* dynamic_rigid = px_rigid_body->isRigidDynamic();
			if(dynamic_rigid && !dynamic_rigid->isSleeping())
			{
				Core::TransformChangedMessage msg;
				msg.new_transform = PxTransformConverter::fromPxTransform(px_rigid_body->getGlobalPose());
				transform_message_sender.sendMessage(msg);
			}
		}
		
		void PxRigidBodyComponent::shutdown()
		{
			physics_subsystem->removeRigidBodyComponent(getName());
			physics_subsystem->getPxScene()->removeActor ( *px_rigid_body );
			px_rigid_body->release();
		}

		Core::ComponentType PxRigidBodyComponent::getType()
		{
			return PX_RIGID_BODY_COMPONENT_TYPE;
		}



	}
}
