#pragma once

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct EngineStartedMessage : public Core::Message{
			constexpr static const char* getTypeName(){return "Engine.EngineStartedMessage";}
		};
	}
}
