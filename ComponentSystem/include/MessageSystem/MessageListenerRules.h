#pragma once

#include <Properties/Properties.h>
#include <vector>

namespace UnknownEngine
{
	namespace Core
	{
		struct MessageListenerRule
		{
			std::string message_type_name;
			std::string receive_policy_type_name;
			Core::Properties receive_policy_options;
		};
		
		typedef std::vector<MessageListenerRule> MessageListenerRules;
		
	}
}