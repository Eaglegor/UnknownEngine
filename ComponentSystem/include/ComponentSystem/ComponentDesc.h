#pragma once

#include <vector>
#include <boost/variant.hpp>

#include <Properties/Properties.h>
#include <ComponentSystem/ComponentType.h>
#include <DescriptorContainer.h>
#include <MessageSystem/Policies/Listener/MessageListenerRules.h>
#include <MessageSystem/Policies/Sender/MessageSenderRules.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IEntity;

		struct ComponentDesc
		{
			std::string name;
			ComponentType type;
			boost::variant<DescriptorContainer, Properties> descriptor;
			MessageListenerRules listener_rules;
			MessageSenderRules sender_rules;
		};

	}
}
