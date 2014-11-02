#pragma once

using std::isfinite;

#include <foundation/PxVec3.h>
#include <Vectors/Vector3.h>

namespace UnknownEngine
{
	namespace Physics
	{
		class PxVec3Converter
		{
		public:
			static physx::PxVec3 toPxVec3(const Math::Vector3 &vec)
			{
				physx::PxVec3 result;
				result.x = vec.x();
				result.y = vec.y();
				result.z = vec.z();
				return result;
			}
			
			static Math::Vector3 fromPxVec3(const physx::PxVec3 &vec)
			{
				Math::Vector3 result;
				result.setX(vec.x);
				result.setY(vec.y);
				result.setZ(vec.z);
				return result;
			}
		};
	}
}