#pragma once
#include <MessageSystem/BaseMessageListener.h>

namespace UnknownEngine
{
	namespace Utils
	{

		class BaseMessageListenersFactory
		{
			public:
				static std::unique_ptr<Core::BaseMessageListener> createBaseMessageListener ( const std::string &name, Core::EngineContext* engine_context, const Core::ReceivedMessageDescriptorsList& received_messages_list )
				{
					std::unique_ptr<Core::BaseMessageListener> listener ( new Core::BaseMessageListener(name, engine_context) );

					initBaseMessageListener(listener, received_messages_list);

					return std::move ( listener );
				}

				static void initBaseMessageListener(std::unique_ptr<Core::BaseMessageListener> &listener, const Core::ReceivedMessageDescriptorsList & received_messages_list)
				{
					initBaseMessageListener(listener.get(), received_messages_list);
				}

				static void initBaseMessageListener(Core::BaseMessageListener* listener, const Core::ReceivedMessageDescriptorsList& received_messages_list)
				{
					for (const Core::ReceivedMessageDesc & message : received_messages_list)
					{
						if (message.receive_policy && listener->getMessagingPoliciesManager().isPrefabReceivePolicyType(message.receive_policy->receive_policy_type_name))
						{
							Core::IMessageReceivePolicy* receive_policy = listener->getMessagingPoliciesManager().createPrefabReceiveMessagePolicy(
								message.receive_policy->receive_policy_type_name,
								message.receive_policy->receive_policy_options
								);

							listener->registerSupportedMessageType(message.message_type_name, receive_policy);
						}
						else
						{
							listener->registerSupportedMessageType(message.message_type_name, nullptr);
						}
					}
				}
		};

	}
}
