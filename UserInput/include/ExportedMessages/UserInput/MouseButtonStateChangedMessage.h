#pragma once

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace IO
	{

		enum class MouseButtonState
		{
			MOUSE_BUTTON_PRESSED,
			MOUSE_BUTTON_UNPRESSED
		};

		/**
		* @brief Mouse button pressed message
		*
		* Indicates that the mouse button is pressed or released
		*
		*/

		struct KeyStateChangedMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "IO.MouseButtonStateChanged";}

			uint32_t mouse_id;

			MouseButtonState new_state;
			uint8_t button_id;
			uint8_t clicks_count;

			int32_t cursor_position_x;
			int32_t cursor_position_y;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
