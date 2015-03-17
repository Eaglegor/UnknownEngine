#pragma once

#include <Vectors/Vector3.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		struct VisibilityData
		{
			bool is_visible;
			
			float percent_visible;
			Math::Vector3 screen_space_aabb_center_position;
		};
	}
}