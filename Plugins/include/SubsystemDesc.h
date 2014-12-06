#pragma once

#include <vector>
#include <MessageSystem/MessageListenerDesc.h>
#include <DescriptorContainer.h>
#include <boost/variant.hpp>
#include <MessageSystem/MessageListenerRules.h>
#include <MessageSystem/MessageSenderRules.h>

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
