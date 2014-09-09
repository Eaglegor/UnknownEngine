#pragma once

#include <vector>
#include <MessageSystem/MessageListenerDesc.h>
#include <DescriptorContainer.h>
#include <boost/variant.hpp>

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
			boost::variant<DescriptorContainer, Properties> descriptor;
		};

	}
}
