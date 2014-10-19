#pragma once

#include <Scalar.h>

namespace UnknownEngine
{
	namespace Physics
	{
		struct PxMaterialDataProviderDesc
		{
			Math::Scalar static_friction;
			Math::Scalar dynamic_friction;
			Math::Scalar restitution;
		};
	}
}