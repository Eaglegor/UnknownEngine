#pragma once

#include <MessageSystem/Message.h>
#include <functional>
#include <string>

namespace UnknownEngine
{
	namespace IO
	{
		struct AddRangeActionMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "IO.InputContext.AddRangeActionMessage";}
			
			std::string context_name;
			std::string action_slot_name;
			std::function< void(Math::Scalar) > action_callback;
		};
	}
}