#include <stdafx.h>
#include <Components/PxShapeOrientedWrapper.h>
#include <PhysXSubsystem.h>
#include <Converters/PxTransformConverter.h>

using std::isfinite;

#include <PxShape.h>
#include <PxPhysics.h>
#include <PxMaterial.h>

namespace UnknownEngine
{
	namespace Physics
	{
		PxShapeOrientedWrapper::PxShapeOrientedWrapper( const physx::PxGeometry& geometry, const physx::PxMaterial *material, PhysXSubsystem* physx_subsystem, bool is_exclusive ):
		px_shape(nullptr)//,
		//physx_subsystem(physx_subsystem)
		{
			createPxShape(geometry, material, physx_subsystem, is_exclusive);
		}

		PxShapeOrientedWrapper::PxShapeOrientedWrapper ( const physx::PxGeometry& geometry, const physx::PxMaterial *material, const Math::Transform& pose_offset, PhysXSubsystem* physx_subsystem, bool is_exclusive ):
		px_shape(nullptr),
		pose_offset(pose_offset)//,
		//physx_subsystem(physx_subsystem)
		{
			createPxShape(geometry, material, physx_subsystem, is_exclusive);
		}
		
		physx::PxShape* PxShapeOrientedWrapper::getPxShape() const
		{
			return px_shape;
		}

		Math::Transform PxShapeOrientedWrapper::getLocalPose() const
		{
			return Math::Transform();
		}
		
		void PxShapeOrientedWrapper::setLocalPose (const Math::Transform& local_pose)
		{
			px_shape->setLocalPose( PxTransformConverter::toPxTransform(local_pose) ); // TODO implement transform offset
		}

		void PxShapeOrientedWrapper::createPxShape ( const physx::PxGeometry& geometry, const physx::PxMaterial *material, PhysXSubsystem* physx_subsystem, bool is_exclusive )
		{
			px_shape = physx_subsystem->getPxPhysics()->createShape(geometry, *material, is_exclusive);
			px_shape->setLocalPose( PxTransformConverter::toPxTransform(pose_offset) );
		}
		
		void PxShapeOrientedWrapper::destroyPxShape()
		{
			px_shape->release();
		}
		
		PxShapeOrientedWrapper::~PxShapeOrientedWrapper()
		{
			destroyPxShape();
		}
		
	}
}