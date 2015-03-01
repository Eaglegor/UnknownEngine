#pragma once

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Utils
	{
		struct SubsystemInitializedMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "Utils.SubsystemInitializedMessage";}
		};
	}
}