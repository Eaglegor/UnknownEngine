#pragma once

#include <string>
#include <vector>
#include <Properties/Properties.h>

namespace UnknownEngine{

	namespace Core{

		struct MessageListenerDesc
		{
			struct MessageDesc
			{
				std::string message_type_name;
				std::string receive_policy_type_name;
				Properties receive_policy_options;
			};

			std::string name;
			std::vector<MessageDesc> messages;
		};

	}
}
