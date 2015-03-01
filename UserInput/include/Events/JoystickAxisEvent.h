#pragma once
#include <cstdint>

namespace UnknownEngine
{
	namespace IO
	{
		struct JoystickAxisEvent
		{
			uint32_t joystick_id;
			uint8_t axis_id;
			int16_t new_value;
		};
	}
}