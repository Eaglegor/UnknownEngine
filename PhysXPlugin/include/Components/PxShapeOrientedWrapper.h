#pragma once

#include <Transform/Transform.h>
#include <AlignedNew.h>

namespace physx
{
	class PxShape;
	class PxGeometry;
	class PxMaterial;
}

namespace UnknownEngine
{
	
	namespace Physics
	{
		
		class PhysXSubsystem;
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) PxShapeOrientedWrapper
		{
		public:
			PxShapeOrientedWrapper(const physx::PxGeometry &geometry, const physx::PxMaterial *material, PhysXSubsystem* physx_subsystem, bool is_exclusive);
			PxShapeOrientedWrapper(const physx::PxGeometry &geometry, const physx::PxMaterial *material, const Core::Transform &pose_offset, PhysXSubsystem* physx_subsystem, bool is_exclusive );
			
			virtual ~PxShapeOrientedWrapper();
			
			void setLocalPose(const Core::Transform &local_pose);
			Core::Transform getLocalPose() const;
			physx::PxShape* getPxShape() const;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

		private:
			void createPxShape( const physx::PxGeometry& geometry, const physx::PxMaterial* material, PhysXSubsystem* physx_subsystem, bool is_exclusive );
			void destroyPxShape();
			
			physx::PxShape* px_shape;
			Core::Transform pose_offset;
			PhysXSubsystem* physx_subsystem;
		};
	}
}