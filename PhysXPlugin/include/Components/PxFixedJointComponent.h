#pragma once

#include <Components/PxJointComponent.h>
#include <Descriptors/Components/PxFixedJointComponentDesc.h>
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
		const Core::ComponentType PX_FIXED_JOINT_COMPONENT_TYPE = Core::ComponentType("Physics.Joint.Fixed");
		
		class PhysXSubsystem;
		
		class PxFixedJointComponent : public PxJointComponent
		{
		public:

			UNKNOWNENGINE_SIMPLE_EXCEPTION(BothActorsNotFound);

			PxFixedJointComponent(const std::string & name, const PxFixedJointComponentDesc & desc, PhysXSubsystem * physics_subsystem, Core::EngineContext * engine_context);
			virtual ~PxFixedJointComponent();
			
			virtual Core::ComponentType getType() const override;
			virtual void init () override;
			virtual void shutdown() override;
			
		private:
			virtual void calculateRelativeTransforms(physx::PxTransform &rel_transform_1, physx::PxTransform &rel_transform_2);

			PxFixedJointComponentDesc desc;
			physx::PxFixedJoint* px_joint;

		};
	}
}