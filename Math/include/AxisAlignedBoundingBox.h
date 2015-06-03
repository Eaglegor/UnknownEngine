#pragma once

#include <Vectors/Vector3.h>

namespace UnknownEngine
{
	namespace Math
	{
		struct AxisAlignedBoundingBox
		{
			Vector3 min;
			Vector3 max;
		};
	}
}