#pragma once

#include <vector>
#include <Properties/Properties.h>
#include <ComponentType.h>
#include <DescriptorContainer.h>
#include <MessageSystem/MessageListenerDesc.h>

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
			DescriptorContainer descriptor; ///< Descriptor of the concrete component. Check if it's set to avoid parsing
			Properties creation_options; ///< String representation of creation options. Parse if descriptor isn't set
			ReceivedMessageDescriptorsList received_messages; ///< Descriptor of received messages
		};

	}
}
