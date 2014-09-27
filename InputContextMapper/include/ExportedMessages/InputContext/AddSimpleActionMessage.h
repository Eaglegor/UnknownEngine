#pragma once

#include <MessageSystem/Message.h>
#include <functional>
#include <string>

namespace UnknownEngine
{
	namespace IO
	{
		struct AddSimpleActionMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "IO.InputContext.AddSimpleActionMessage";}
			
			std::string context_name;
			std::string action_slot_name;
			std::function<void()> action_callback;
		};
	}
}