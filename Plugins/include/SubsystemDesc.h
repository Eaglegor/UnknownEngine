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
		/**
		 * @brief Descriptor of subsystem (plugin) to load
		 */
		struct SubsystemDesc
		{
			std::string name; ///< **Unique** name of subsystem
			std::string module_name; ///< Shared library filename
			boost::variant<DescriptorContainer, Properties> descriptor;
			MessageListenerRules listener_rules;
			MessageSenderRules sender_rules;
		};

	}
}
