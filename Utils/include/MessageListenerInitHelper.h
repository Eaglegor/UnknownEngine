#pragma once

#include <MessageSystem/BaseMessageListener.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Utils
	{
		class MessageListenerInitHelper
		{
			public:

				static setSupportedMessageTypes ( Core::BaseMessageListener* listener, const Core::ReceivedMessageDescriptorsList& received_messages_list )
				{
					for ( const Core::ReceivedMessageDesc & message : received_messages_list )
					{
						listener->registerSupportedMessageType ( message.message_type_name );
					}
				}
				
				static registerListener( Core::BaseMessageListener* listener, const Core::ReceivedMessageDescriptorsList& received_messages_list, Core::MessageDispatcher* message_dispatcher )
				{
					for ( const Core::ReceivedMessageDesc & message : received_messages_list )
					{
						if(message.receive_policy)
						{
							Core::MessagingPoliciesManager& messaging_policies_manager;
							if(messaging_policies_manager.isPrefabReceivePolicyType(message.receive_policy->receive_policy_type_name))
							{
								Core::IMessageReceivePolicy* receive_policy = messaging_policies_manager.createPrefabDeliveryMessagePolicy(
									message.receive_policy->receive_policy_type_name,
									message.receive_policy->receive_policy_options
								);
								
								message_dispatcher->addListener(message.message_type_name, listener, receive_policy);
							}
						}
					}
				}
				
				static unregisterListener( Core::BaseMessageListener* listener, Core::MessageDispatcher* message_dispatcher )
				{
					message_dispatcher->removeListener(listener);
				}
				
		};
	}
}

