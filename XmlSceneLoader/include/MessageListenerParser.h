#pragma once

#include <MessageSystem/Policies/Listener/MessageListenerRules.h>
#include <MessageSystem/Policies/Sender/MessageSenderRules.h>
#include <boost/property_tree/ptree_fwd.hpp>

namespace UnknownEngine
{
	namespace Loader
	{

		class ConstantsHolder;

		class MessageListenerParser
		{
			public:
				struct MessagingRules
				{
					Core::MessageListenerRules listener_rules;
					Core::MessageSenderRules sender_rules;
				};
				
				MessageListenerParser();
				static MessagingRules parseMessagingRules(const boost::property_tree::ptree &event_listener_node, const ConstantsHolder* constants_holder);
				static Core::MessageListenerRules parseListenerRules ( const boost::property_tree::ptree &event_listener_node, const ConstantsHolder* constants_holder );
				static Core::MessageSenderRules parseSenderRules ( const boost::property_tree::ptree &event_listener_node, const ConstantsHolder* constants_holder );
				
			private:
				static Core::MessageListenerRule parseListenerRule ( const boost::property_tree::ptree &event_listener_node, const ConstantsHolder* constants_holder );
				static Core::MessageSenderRule parseSenderRule ( const boost::property_tree::ptree &event_listener_node, const ConstantsHolder* constants_holder );
				//static Core::ReceivedMessageDescriptorsList parseMessageListener ( const boost::property_tree::ptree &event_listener_node, const ConstantsHolder* constants_holder );
				//static UnknownEngine::Core::ReceivedMessageDesc parseMessageDesc ( const boost::property_tree::ptree &message_node, const ConstantsHolder* constants_holder );
		};

	} // namespace Core
} // namespace UnknownEngine
