#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <Descriptors/Components/PxRigidBodyComponentDesc.h>
#include "IPhysXUpdateListener.h"
#include <AlignedNew.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <ComponentInterfaces/PhysX/IPhysXRigidBodyComponent.h>
#include <ComponentInterfaces/Transform/TransformHolderComponent.h>
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
		class ILogger;
	}

	namespace Physics
	{

		class PhysXSubsystem;
		class PxShapeOrientedWrapper;
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) PxRigidBodyComponent : 
		IPhysXUpdateListener,
		public Core::BaseComponent,
		public ComponentInterfaces::IPhysXRigidBodyComponent,
		public ComponentInterfaces::TransformHolderComponent
		{
		public:
			PxRigidBodyComponent( const std::string & name, const PxRigidBodyComponentDesc & desc, PhysXSubsystem * physics_subsystem);
			virtual ~PxRigidBodyComponent();
			
			constexpr static const char* getTypeName(){return "PhysX.RigidBody";}
			virtual Core::ComponentType getType() const override {return getTypeName();}
			virtual void init () override;
			virtual void shutdown() override;
			
			void setTransform(const Math::Transform &transform);

			virtual physx::PxRigidActor* getPxRigidActor() override { return px_rigid_body; }

			virtual void update() override;
			
			virtual IComponentInterface * getInterface ( const Core::ComponentType & type );
			
			virtual Math::Quaternion getOrientation();
			virtual Math::Vector3 getPosition();
			virtual Math::Transform getTransform();
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			Core::MessageSender<Core::TransformChangedMessage> transform_message_sender;
			
			PxRigidBodyComponentDesc desc;
			PhysXSubsystem* physics_subsystem;
			physx::PxRigidActor* px_rigid_body;
			PxShapeOrientedWrapper* px_shape;
			bool first_update_passed;

			Core::ILogger* logger;
			Math::Transform current_transform;
		};
	}
}