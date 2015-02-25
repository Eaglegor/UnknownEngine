#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <Descriptors/Components/PxFixedJointComponentDesc.h>
#include <ComponentInterfaces/PhysX/IPhysXRigidBodyComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <LogHelper.h>
#include <Exception.h>

namespace physx
{
	class PxRigidActor;
	class PxFixedJoint;
	class PxTransform;
}

namespace UnknownEngine
{
	namespace Physics
	{
		class PhysXSubsystem;
		
		class PxFixedJointComponent : public Core::BaseComponent
		{
		public:

			UNKNOWNENGINE_SIMPLE_EXCEPTION(BothActorsNotFound);

			PxFixedJointComponent(const std::string & name, const PxFixedJointComponentDesc & desc, PhysXSubsystem * physics_subsystem);
			virtual ~PxFixedJointComponent();
			
			constexpr static const char* getTypeName(){return "PhysX.FixedJoint";}
			virtual Core::ComponentType getType() const override {return getTypeName();}
			virtual void init () override;
			virtual void shutdown() override;
			
		private:
			virtual void calculateRelativeTransforms(physx::PxTransform &rel_transform_1, physx::PxTransform &rel_transform_2);

			PxFixedJointComponentDesc desc;
			physx::PxFixedJoint* px_joint;
			
			PhysXSubsystem* physics_subsystem;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::IPhysXRigidBodyComponent> rigid_body1;
			Core::ComponentInterfacePtr<ComponentInterfaces::IPhysXRigidBodyComponent> rigid_body2;
			
			physx::PxRigidActor* actor1;
			physx::PxRigidActor* actor2;

			Core::LogHelper logger;
			
		};
	}
}