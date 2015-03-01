#pragma once
#include <cstdint>

namespace UnknownEngine
{
	namespace IO
	{
		struct MouseMovedEvent
		{
			uint32_t mouse_id;
			int32_t new_x;
			int32_t new_y;
			int32_t delta_x;
			int32_t delta_y;
		};
	}
}