#pragma once

#include <Scalar.h>

namespace UnknownEngine
{
	namespace Physics
	{
		struct PxBoxGeometryDataProviderDesc
		{
			Math::Scalar width; // X
			Math::Scalar height; // Y
			Math::Scalar depth; // Z
		};
	}
}