#pragma once

using std::isfinite;

#include <foundation/PxTransform.h>
#include <Transform/Transform.h>
#include <Converters/PxVec3Converter.h>
#include <Converters/PxQuatConverter.h>

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
				result.p = PxVec3Converter::toPxVec3(transform.getPosition());
				result.q = PxQuatConverter::toPxQuat(transform.getOrientation());
				return result;
			}
			
			static Math::Transform fromPxTransform(const physx::PxTransform &transform)
			{
				Math::Transform result;
				result.setPosition( PxVec3Converter::fromPxVec3(transform.p) );
				result.setOrientation( PxQuatConverter::fromPxQuat(transform.q) );
				return result;
			}
		};
	}
}