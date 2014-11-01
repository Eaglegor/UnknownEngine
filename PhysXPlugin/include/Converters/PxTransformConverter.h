#pragma once

using std::isfinite;

#include <foundation/PxTransform.h>
#include <Transform/Transform.h>

namespace UnknownEngine
{
	namespace Physics
	{
		class PxTransformConverter
		{
		public:
			static physx::PxTransform toPxTransform(const Math::Transform &transform)
			{
				physx::PxTransform result;
				const Math::Vector3 &position = transform.getPosition();
				result.p.x = position.x();
				result.p.y = position.y();
				result.p.z = position.z();
				const Math::Quaternion &orientation = transform.getOrientation();
				result.q.w = orientation.w();
				result.q.x = orientation.x();
				result.q.y = orientation.y();
				result.q.z = orientation.z();
				return result;
			}
			
			static Math::Transform fromPxTransform(const physx::PxTransform &transform)
			{
				Math::Transform result;
				result.setPosition( Math::Vector3(transform.p.x, transform.p.y, transform.p.z) );
				result.setOrientation( Math::Quaternion(transform.q.w, transform.q.x, transform.q.y, transform.q.z) );
				return result;
			}
		};
	}
}