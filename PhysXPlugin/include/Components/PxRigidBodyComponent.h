#pragma once

#include <Objects/BaseComponent.h>
#include <Descriptors/Components/PxRigidBodyComponentDesc.h>
#include <AlignedNew.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <memory>

namespace physx
{
	class PxRigidActor;
}

namespace UnknownEngine
{

	namespace Core
	{
		class BaseMessageListener;
		struct TransformChangedMessage;
	}

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
			void initMessageListener(const Core::ReceivedMessageDescriptorsList& received_messages);
			
			void setTransform(const Math::Transform &transform);

			UNKNOWNENGINE_INLINE
			physx::PxRigidActor* getPxRigidActor(){ return px_rigid_body; }

			virtual void update();

			void onTransformChanged(const Core::TransformChangedMessage &msg);
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			
			std::unique_ptr<Core::BaseMessageListener> listener;
			Core::MessageSender<Core::TransformChangedMessage> transform_message_sender;

			
			PxRigidBodyComponentDesc desc;
			PhysXSubsystem* physics_subsystem;
			physx::PxRigidActor* px_rigid_body;
			PxShapeOrientedWrapper* px_shape;
			bool first_update_passed;

			Core::EngineContext* engine_context;

			std::unique_ptr<Utils::LogHelper> log_helper;
		};
	}
}