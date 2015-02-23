#pragma once

#include <MouseButtonState.h>
#include <cstdint>

namespace UnknownEngine
{
	namespace IO
	{
		struct MouseButtonEvent
		{
			uint32_t mouse_id;
			
			uint8_t button_id;
			MouseButtonState new_state;
		};
	}
}