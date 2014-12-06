#pragma once

#include <MessageSystem/Message.h>
#include <Keys.h>
#include <KeyState.h>

namespace UnknownEngine
{
	namespace IO
	{
		struct KeyStateChangedMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "IO.KeyStateChanged";}
			
			KeyState new_state;
			Key key;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
