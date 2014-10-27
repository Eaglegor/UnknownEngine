#pragma once

#include <Objects/BaseComponent.h>
#include <Descriptors/Components/PxRigidBodyComponentDesc.h>
#include <AlignedNew.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/TransformChangedMessage.h>

namespace physx
{
	class PxRigidActor;
}

namespace UnknownEngine
{
	namespace Physics
	{

		const Core::ComponentType PX_RIGID_BODY_COMPONENT_TYPE = Core::ComponentType("Physics.RigidBody");
		
		class PhysXSubsystem;
		class PxShapeOrientedWrapper;
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) PxRigidBodyComponent : public Core::BaseComponent
		{
		public:
			PxRigidBodyComponent( const std::string & name, const UnknownEngine::Physics::PxRigidBodyComponentDesc & desc, UnknownEngine::Physics::PhysXSubsystem * physics_subsystem, UnknownEngine::Core::EngineContext * engine_context );
			virtual ~PxRigidBodyComponent();
			
			virtual Core::ComponentType getType();
			virtual void init ( const Core::Entity* parent_entity );
			virtual void shutdown();
			
			virtual void update();
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			
			Core::MessageSender<Core::TransformChangedMessage> transform_message_sender;
			
			PxRigidBodyComponentDesc desc;
			PhysXSubsystem* physics_subsystem;
			physx::PxRigidActor* px_rigid_body;
			PxShapeOrientedWrapper* px_shape;
			
		};
	}
}