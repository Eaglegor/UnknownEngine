#pragma once

#include <vector>
#include <DescriptorContainer.h>
#include <boost/variant.hpp>
#include <MessageSystem/Policies/Listener/MessageListenerRules.h>
#include <MessageSystem/Policies/Sender/MessageSenderRules.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct SubsystemDesc
		{
			std::string name;
			std::string module_name;
			boost::variant<DescriptorContainer, Properties> descriptor;
			MessageListenerRules listener_rules;
			MessageSenderRules sender_rules;
		};

	}
}
