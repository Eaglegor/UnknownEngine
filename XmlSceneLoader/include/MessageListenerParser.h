#ifndef UNKNOWNENGINE_CORE_MESSAGELISTENERPARSER_H
#define UNKNOWNENGINE_CORE_MESSAGELISTENERPARSER_H

#include <MessageSystem/MessageListenerDesc.h>
#include <boost/property_tree/ptree_fwd.hpp>

namespace UnknownEngine {
	namespace Loader {

		class ConstantsHolder;

		class MessageListenerParser
		{
			public:
				MessageListenerParser();
				static Core::MessageListenerDesc parseMessageListener(const boost::property_tree::ptree &event_listener_node, const ConstantsHolder* constants_holder);
				static UnknownEngine::Core::MessageListenerDesc::MessageDesc parseMessageDesc(const boost::property_tree::ptree &message_node, const ConstantsHolder* constants_holder);
		};

	} // namespace Core
} // namespace UnknownEngine

#endif // UNKNOWNENGINE_CORE_MESSAGELISTENERPARSER_H
