#pragma once

#include <Components/PxJointComponent.h>
#include <Descriptors/Components/PxFixedJointComponentDesc.h>
#include <Exception.h>

namespace physx
{
	class PxRigidActor;
	class PxFixedJoint;
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
			
			virtual Core::ComponentType getType();
			virtual void init ( const Core::Entity* parent_entity );
			virtual void shutdown();
			
		private:
			PxFixedJointComponentDesc desc;
			physx::PxFixedJoint* px_joint;

		};
	}
}