#include <Components/PxShapeOrientedWrapper.h>
#include <PhysXSubsystem.h>

using std::isfinite;

#include <PxShape.h>
#include <PxPhysics.h>
#include <PxMaterial.h>

namespace UnknownEngine
{
	namespace Physics
	{
		PxShapeOrientedWrapper::PxShapeOrientedWrapper( const physx::PxGeometry& geometry, const physx::PxMaterial *material, PhysXSubsystem* physx_subsystem ):
		px_shape(nullptr),
		physx_subsystem(physx_subsystem)
		{
			createPxShape(geometry, material, physx_subsystem);
		}

		PxShapeOrientedWrapper::PxShapeOrientedWrapper ( const physx::PxGeometry& geometry, const physx::PxMaterial *material, const Core::Transform& pose_offset, PhysXSubsystem* physx_subsystem ):
		px_shape(nullptr),
		pose_offset(pose_offset),
		physx_subsystem(physx_subsystem)
		{
			createPxShape(geometry, material, physx_subsystem);
		}
		
		physx::PxShape* PxShapeOrientedWrapper::getPxShape() const
		{
			return px_shape;
		}

		Core::Transform PxShapeOrientedWrapper::getLocalPose() const
		{
			return Core::Transform();
		}
		
		void PxShapeOrientedWrapper::setLocalPose (const Core::Transform& local_pose)
		{
			px_shape->setLocalPose(physx::PxTransform(physx::PxIdentity)); // TODO implement transform offset
		}

		void PxShapeOrientedWrapper::createPxShape ( const physx::PxGeometry& geometry, const physx::PxMaterial *material, PhysXSubsystem* physx_subsystem )
		{
			physx_subsystem->getPxPhysics()->createShape(geometry, *material);
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