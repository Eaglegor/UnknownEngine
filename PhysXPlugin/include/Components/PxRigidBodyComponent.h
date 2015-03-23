#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <Descriptors/Components/PxRigidBodyComponentDesc.h>
#include "IPhysXUpdateListener.h"
#include <AlignedNew.h>
#include <ComponentInterfaces/Physics/PhysX/IPhysXRigidBodyComponent.h>
#include <ComponentInterfaces/Transform/TransformHolderComponent.h>
#include <ComponentInterfaces/Transform/TransformNotifierComponent.h>
#include <ComponentInterfaces/Transform/MovableComponent.h>
#include <memory>
#include <Concurrency/DataStructures/LockingConcurrentSet.h>
#include <Observer.h>

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
		public ComponentInterfaces::TransformHolderComponent,
		public ComponentInterfaces::TransformNotifierComponent,
		public ComponentInterfaces::MovableComponent
		{
		public:
			PxRigidBodyComponent( const std::string & name, const PxRigidBodyComponentDesc & desc, PhysXSubsystem * physics_subsystem);
			virtual ~PxRigidBodyComponent();
			
			constexpr static const char* getTypeName(){return "PhysX.RigidBody";}
			virtual Core::ComponentType getType() const override {return getTypeName();}
			virtual bool init () override;
			virtual void shutdown() override;
			
			virtual physx::PxRigidActor* getPxRigidActor() override { return px_rigid_body; }

			virtual void update() override;
			
			virtual IComponentInterface * getInterface ( const Core::ComponentType & type );
			
			virtual Math::Quaternion getOrientation() override;
			virtual Math::Vector3 getPosition() override;
			virtual Math::Transform getTransform() override;
			
			virtual void addListener ( ComponentInterfaces::MovableComponent * movable_component ) override;
			virtual void removeListener ( ComponentInterfaces::MovableComponent * movable_component ) override;
			
			virtual void setOrientation ( const Math::Quaternion & quaternion ) override;
			virtual void setPosition ( const Math::Vector3 & position ) override;
			virtual void setTransform(const Math::Transform &transform) override;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			PxRigidBodyComponentDesc desc;
			PhysXSubsystem* physics_subsystem;
			physx::PxRigidActor* px_rigid_body;
			PxShapeOrientedWrapper* px_shape;
			bool first_update_passed;

			//Core::ILogger* logger;
			Math::Transform current_transform;
			
			Utils::Observer<ComponentInterfaces::MovableComponent> transform_listeners;
		};
	}
}