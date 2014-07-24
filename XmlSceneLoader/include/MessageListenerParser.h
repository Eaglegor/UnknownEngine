#pragma once

#include <MessageSystem/MessageListenerDesc.h>
#include <boost/property_tree/ptree_fwd.hpp>

namespace UnknownEngine {
	namespace Loader {

		class ConstantsHolder;

		class MessageListenerParser
		{
			public:
				MessageListenerParser();
				static Core::ReceivedMessageDescriptorsList&& parseMessageListener(const boost::property_tree::ptree &event_listener_node, const ConstantsHolder* constants_holder);
				static UnknownEngine::Core::ReceivedMessageDesc parseMessageDesc(const boost::property_tree::ptree &message_node, const ConstantsHolder* constants_holder);
		};

	} // namespace Core
} // namespace UnknownEngine
