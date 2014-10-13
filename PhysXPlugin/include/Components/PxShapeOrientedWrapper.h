#pragma once

#include <Transform/Transform.h>

namespace physx
{
	class PxShape;
	class PxGeometry;
}

namespace UnknownEngine
{
	
	namespace Physics
	{
		
		class PhysXSubsystem;
		
		class PxShapeOrientedWrapper
		{
		public:
			PxShapeOrientedWrapper(const physx::PxGeometry &geometry, PhysXSubsystem* physx_subsystem);
			explicit PxShapeOrientedWrapper(const physx::PxGeometry &geometry, const Core::Transform &pose_offset, PhysXSubsystem* physx_subsystem);
			
			void setLocalPose(const Core::Transform &local_pose);
			physx::PxShape* getPxShape() const;
			
		private:
			void createPxShape(const physx::PxGeometry &geometry, PhysXSubsystem* physx_subsystem);
			void destroyPxShape();
			
			physx::PxShape* px_shape;
			Core::Transform pose_offset;
			PhysXSubsystem* physx_subsystem;
		};
	}
}