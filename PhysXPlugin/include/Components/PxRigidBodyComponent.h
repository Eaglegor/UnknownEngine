#pragma once

#include <Objects/BaseComponent.h>
#include <Descriptors/Components/PxRigidBodyComponentDesc.h>

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
		
		class PxRigidBodyComponent : public Core::BaseComponent
		{
		public:
			PxRigidBodyComponent(const std::string &name, const PxRigidBodyComponentDesc &desc, PhysXSubsystem* physics_subsystem);
			virtual ~PxRigidBodyComponent();
			
			virtual Core::ComponentType getType();
			virtual void init ( const Core::Entity* parent_entity );
			virtual void shutdown();
			
			
		private:
			PxRigidBodyComponentDesc desc;
			PhysXSubsystem* physics_subsystem;
			physx::PxRigidActor* px_rigid_body;
			PxShapeOrientedWrapper* px_shape;
			
		};
	}
}