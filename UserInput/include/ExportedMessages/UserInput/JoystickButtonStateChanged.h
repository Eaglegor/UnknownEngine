#pragma once

#include <MessageSystem/Message.h>
#include <JoystickButtonState.h>
#include <cstdint>

namespace UnknownEngine
{
	namespace IO
	{
		struct JoystickButtonStateChangedMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "IO.JoystickButtonStateChanged";}

			int32_t joystick_id;
			uint8_t button_id;
			JoystickButtonState new_state;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
