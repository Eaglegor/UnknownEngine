#pragma once

#include <cstdint>
#include <JoystickButtonState.h>

namespace UnknownEngine
{
	namespace IO
	{
		struct JoystickButtonEvent
		{
			uint32_t joystick_id;
			uint8_t button_id;
			JoystickButtonState new_state;
		};
	}
}