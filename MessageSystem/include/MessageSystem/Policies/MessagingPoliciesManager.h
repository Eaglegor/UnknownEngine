#pragma once

#include <MessageSystem_export.h>
#include <unordered_map>
#include <MessageSystem/Policies/Listener/IMessageReceivePolicy.h>
#include <MessageSystem/Policies/Sender/IMessageDeliveryPolicy.h>
#include <Singleton.h>
#include <MessageSystem/Policies/Listener/IMessageReceivePolicyFactory.h>
#include <MessageSystem/Policies/Sender/IMessageDeliveryPolicyFactory.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Core
	{

		struct MessageDeliveryPolicyDesc;
		struct MessageReceivePolicyDesc;

		class StandardMessageDeliveryPoliciesFactory;
		class StandardMessageReceivePoliciesFactory;

		class EngineContext;

		class MessagingPoliciesManager : public Singleton<MessagingPoliciesManager>
		{
			public:
				MessagingPoliciesManager();
				~MessagingPoliciesManager();
				
				MESSAGESYSTEM_EXPORT
				void addMessageReceivePolicyFactory(IMessageReceivePolicyFactory* factory);

				MESSAGESYSTEM_EXPORT
				void addMessageDeliveryPolicyFactory(IMessageDeliveryPolicyFactory* factory);

				MESSAGESYSTEM_EXPORT
				void removeMessageReceivePolicyFactory(IMessageReceivePolicyFactory* factory);

				MESSAGESYSTEM_EXPORT
				void removeMessageDeliveryPolicyFactory(IMessageDeliveryPolicyFactory* factory);

				MESSAGESYSTEM_EXPORT
				IMessageReceivePolicy* createMessageReceivePolicy(const MessageReceivePolicyDesc& desc);

				MESSAGESYSTEM_EXPORT
				IMessageDeliveryPolicy* createMessageDeliveryPolicy(const MessageDeliveryPolicyDesc& desc);

				MESSAGESYSTEM_EXPORT
				void destroyMessageReceivePolicy(IMessageReceivePolicy* policy);

				MESSAGESYSTEM_EXPORT
				void destroyMessageDeliveryPolicy(IMessageDeliveryPolicy* policy);

			private:
				IMessageReceivePolicyFactory* findReceivePolicyFactory(const MessageReceivePolicyType& type);
				IMessageDeliveryPolicyFactory* findDeliveryPolicyFactory( const MessageDeliveryPolicyType& type );

				void createStandardFactoires();
				void destroyStandardFactoires();

				std::unordered_map<std::string, IMessageReceivePolicyFactory*> receive_policy_factories;
				std::unordered_map<std::string, IMessageDeliveryPolicyFactory*> delivery_policy_factories;
				
				StandardMessageReceivePoliciesFactory* standard_receive_policy_factory;
				StandardMessageDeliveryPoliciesFactory* standard_delivery_policy_factory;
				
				LogHelper logger;
		};

#ifdef _MSC_VER
#ifndef MessageSystem_EXPORTS
		extern template class MESSAGESYSTEM_EXPORT Singleton<MessagingPoliciesManager>;
#else
		template class MESSAGESYSTEM_EXPORT Singleton<MessagingPoliciesManager>;
#endif
#endif

	} // namespace Core
} // namespace UnknownEngine
