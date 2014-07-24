#pragma once

#include <vector>
#include <MessageSystem/MessageListenerDesc.h>
#include <DescriptorContainer.h>

namespace UnknownEngine
{
	namespace Core
	{
		/**
		 * @brief Descriptor of subsystem (plugin) to load
		 */
		struct SubsystemDesc
		{
			std::string name; ///< **Unique** name of subsystem
			std::string module_name; ///< Shared library filename
			ReceivedMessageDescriptorsList received_messages; ///< List of message subscriptions
			Properties creation_options; ///< String representation of creation options
			DescriptorContainer prepared_descriptor; ///< Optional prepared descriptor. Check if this is not empty to avoid parsing.
		};

	}
}
