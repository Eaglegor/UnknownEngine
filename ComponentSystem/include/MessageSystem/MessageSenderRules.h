#pragma once

#include <Properties/Properties.h>
#include <vector>

namespace UnknownEngine
{
	namespace Core
	{
		struct MessageSenderRule
		{
			std::string message_type_name;
			std::string delivery_policy_type_name;
			Core::Properties delivery_policy_options;
		};
		
		typedef std::vector<MessageSenderRule> MessageSenderRules;
	}
}