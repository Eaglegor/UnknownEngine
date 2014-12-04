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

		/**
		 * @brief Descriptor of component to be passed to the component factory.
		 */
		struct ComponentDesc
		{
			std::string name; ///< Local name of component in the entity
			ComponentType type; ///< Type identifier of component
			boost::variant<DescriptorContainer, Properties> descriptor;
			ReceivedMessageDescriptorsList received_messages; ///< Descriptor of received messages
			MessageListenerRules listener_rules;
			MessageSenderRules sender_rules;
		};

	}
}
