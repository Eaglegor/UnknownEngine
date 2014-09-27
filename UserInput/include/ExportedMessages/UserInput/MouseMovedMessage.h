#pragma once

#include <MessageSystem/Message.h>
#include <cstdint>

namespace UnknownEngine
{
	namespace IO
	{

		/**
		* @brief Mouse moved message
		*
		*/

		struct MouseMovedMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "IO.MouseMoved";}

			uint32_t mouse_id;
			int32_t new_x;
			int32_t new_y;
			int32_t delta_x;
			int32_t delta_y;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
