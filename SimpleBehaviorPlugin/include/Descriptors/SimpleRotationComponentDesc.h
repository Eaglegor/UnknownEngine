#pragma once

#include <AlignedNew.h>
#include <Transform/Transform.h>
#include <ComponentSystem/IComponent.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		UNKNOWNENGINE_ALIGNED_STRUCT(16) SimpleRotationComponentDesc
		{
			Math::Transform initial_transform;
			Core::IComponent* update_frame_provider = nullptr;
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Behavior::SimpleRotationComponentDesc);