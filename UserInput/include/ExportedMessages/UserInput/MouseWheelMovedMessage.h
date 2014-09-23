#pragma once

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace IO
	{

		/**
		* @brief Mouse wheel moved message
		*
		*/

		struct MouseWheeMovedMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "IO.MouseWheelMoved";}

			uint32_t mouse_id;
			int32_t delta_x;
			int32_t delta_y;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
