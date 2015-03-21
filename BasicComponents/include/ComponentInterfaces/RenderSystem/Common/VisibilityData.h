#pragma once

#include <Scalar.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		struct VisibilityData
		{
			bool is_visible;
			Math::Scalar visibility_ratio;
			
			VisibilityData():
			is_visible(false),
			visibility_ratio(0)
			{}
		};
	}
}