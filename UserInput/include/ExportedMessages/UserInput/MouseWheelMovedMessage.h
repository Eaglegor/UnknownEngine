#pragma once

#include <MessageSystem/Message.h>

#ifdef _MSC_VER
	typedef __int32 int32_t;
	typedef unsigned __int32 uint32_t;
#endif

namespace UnknownEngine
{
	namespace IO
	{

		/**
		* @brief Mouse wheel moved message
		*
		*/

		struct MouseWheelMovedMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "IO.MouseWheelMoved";}

			uint32_t mouse_id;
			int32_t delta_x;
			int32_t delta_y;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
