#pragma once

#include <string>
#include <vector>
#include <Properties/Properties.h>

namespace UnknownEngine
{

	namespace Core
	{
		struct ReceivedMessageDesc
		{
			struct ReceivePolicyDesc
			{
				std::string receive_policy_type_name;
				Properties receive_policy_options;
			};
			
			std::string message_type_name;
			boost::optional<ReceivePolicyDesc> receive_policy;
			
		};

		typedef std::vector<ReceivedMessageDesc> ReceivedMessageDescriptorsList;

	}
}
