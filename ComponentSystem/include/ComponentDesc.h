#pragma once

#include <vector>
#include <boost/variant.hpp>


#include <Properties/Properties.h>
#include <ComponentType.h>
#include <DescriptorContainer.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <MessageSystem/MessageListenerRules.h>
#include <MessageSystem/MessageSenderRules.h>

namespace UnknownEngine
{
	namespace Core
	{
		class Entity;

		struct ComponentDesc
		{
			std::string name;
			ComponentType type;
			boost::variant<DescriptorContainer, Properties> descriptor;
			ReceivedMessageDescriptorsList received_messages;
			MessageListenerRules listener_rules;
			MessageSenderRules sender_rules;
		};

	}
}
