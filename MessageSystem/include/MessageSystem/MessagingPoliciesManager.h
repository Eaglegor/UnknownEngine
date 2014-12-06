#pragma once

#include <MessageSystem_export.h>
#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>
#include <Exception.h>
#include <MessageSystem/Policies/MessagePolicyType.h>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>
#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <Properties/Properties_fwd.h>
#include <Singleton.h>
#include <NumericIdentifierType.h>
#include <Properties/PropertiesTree.h>
#include <Dictionary.h>
#include <MessageSystem/IMessageReceivePolicyFactory.h>
#include <MessageSystem/IMessageDeliveryPolicyFactory.h>

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

				std::unordered_map<NumericIdentifierType, IMessageReceivePolicyFactory*> receive_policy_factories;
				std::unordered_map<NumericIdentifierType, IMessageDeliveryPolicyFactory*> delivery_policy_factories;
				
				StandardMessageReceivePoliciesFactory* standard_receive_policy_factory;
				StandardMessageDeliveryPoliciesFactory* standard_delivery_policy_factory;
				
				typedef Utils::Dictionary<NumericIdentifierType, std::string> InternalDictionaryType;
				InternalDictionaryType internal_dictionary;
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
