#pragma once

#include <MessageSystem/Message.h>
#include <cstdint>

namespace UnknownEngine
{
	namespace IO
	{
		struct JoystickAxisMovedMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "IO.JoystickAxisMoved";}

			int32_t joystick_id;
			uint8_t axis_id;
			int16_t new_value;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
