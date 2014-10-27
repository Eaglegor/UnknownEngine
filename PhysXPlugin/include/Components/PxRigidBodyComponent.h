#pragma once

#include <Objects/BaseComponent.h>
#include <Descriptors/Components/PxRigidBodyComponentDesc.h>
#include <AlignedNew.h>

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
			PxRigidBodyComponent(const std::string &name, const PxRigidBodyComponentDesc &desc, PhysXSubsystem* physics_subsystem);
			virtual ~PxRigidBodyComponent();
			
			virtual Core::ComponentType getType();
			virtual void init ( const Core::Entity* parent_entity );
			virtual void shutdown();
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			PxRigidBodyComponentDesc desc;
			PhysXSubsystem* physics_subsystem;
			physx::PxRigidActor* px_rigid_body;
			PxShapeOrientedWrapper* px_shape;
			
		};
	}
}