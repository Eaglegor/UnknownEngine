#pragma once

#include <Objects/BaseComponent.h>
#include <Descriptors/Components/PxRigidBodyComponentDesc.h>
#include <AlignedNew.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <memory>

namespace physx
{
	class PxRigidActor;
}

namespace UnknownEngine
{

	namespace Utils
	{
		class LogHelper;
	}

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
			
			UNKNOWNENGINE_INLINE
			physx::PxRigidActor* getPxRigidActor(){ return px_rigid_body; }

			virtual void update();
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			
			Core::MessageSender<Core::TransformChangedMessage> transform_message_sender;
			
			PxRigidBodyComponentDesc desc;
			PhysXSubsystem* physics_subsystem;
			physx::PxRigidActor* px_rigid_body;
			PxShapeOrientedWrapper* px_shape;
			bool first_update_passed;

			std::unique_ptr<Utils::LogHelper> log_helper;
			
		};
	}
}