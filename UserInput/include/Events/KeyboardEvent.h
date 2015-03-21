#pragma once

#include <Keys.h>
#include <KeyState.h>

namespace UnknownEngine
{
	namespace IO
	{
		struct KeyboardEvent
		{
			uint32_t keyboard_id;
			Key key;
			KeyState new_state;
			char character;
		};
	}
}