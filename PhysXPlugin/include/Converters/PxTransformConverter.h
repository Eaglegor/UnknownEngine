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
			static physx::PxTransform toPxTransform(const Core::Transform &transform)
			{
				return physx::PxTransform();
			}
			
			static Core::Transform fromPxTransform(const physx::PxTransform &transform)
			{
				return Core::Transform();
			}
		};
	}
}