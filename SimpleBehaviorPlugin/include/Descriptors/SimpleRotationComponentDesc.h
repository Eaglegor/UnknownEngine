#pragma once

#include <AlignedNew.h>
#include <Transform/Transform.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		UNKNOWNENGINE_ALIGNED_STRUCT(16) SimpleRotationComponentDesc
		{
			Math::Transform initial_transform;
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Behavior::SimpleRotationComponentDesc);