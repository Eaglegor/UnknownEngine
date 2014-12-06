#pragma once

#include <MessageSystem/Message.h>
#include <cstdint>

namespace UnknownEngine
{
	namespace IO
	{
		struct MouseWheelMovedMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "IO.MouseWheelMoved";}

			uint32_t mouse_id;
			int32_t delta_x;
			int32_t delta_y;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
