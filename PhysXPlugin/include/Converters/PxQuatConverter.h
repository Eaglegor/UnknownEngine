#pragma once

using std::isfinite;

#include <foundation/PxQuat.h>
#include <Quaternion.h>

namespace UnknownEngine
{
	namespace Physics
	{
		class PxQuatConverter
		{
		public:
			static physx::PxQuat toPxQuat(const Math::Quaternion &q)
			{
				physx::PxQuat result;
				result.x = q.x();
				result.y = q.y();
				result.z = q.z();
				result.w = q.w();
				return result;
			}
			
			static Math::Quaternion fromPxQuat(const physx::PxQuat &q)
			{
				Math::Quaternion result;
				result.setX(q.x);
				result.setY(q.y);
				result.setZ(q.z);
				result.setW(q.w);
				return result;
			}
		};
	}
}