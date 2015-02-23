#pragma once
#include <cstdint>

namespace UnknownEngine
{
	namespace IO
	{
		struct MouseWheelEvent
		{
			uint32_t mouse_id;
			int32_t delta;
		};
	}
}