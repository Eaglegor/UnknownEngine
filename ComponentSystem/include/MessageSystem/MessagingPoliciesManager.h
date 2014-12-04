#pragma once

#include <ComponentSystem_export.h>
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
				
				COMPONENTSYSTEM_EXPORT
				void addMessageReceivePolicyFactory(IMessageReceivePolicyFactory* factory);

				COMPONENTSYSTEM_EXPORT
				void addMessageDeliveryPolicyFactory(IMessageDeliveryPolicyFactory* factory);

				COMPONENTSYSTEM_EXPORT
				void removeMessageReceivePolicyFactory(IMessageReceivePolicyFactory* factory);

				COMPONENTSYSTEM_EXPORT
				void removeMessageDeliveryPolicyFactory(IMessageDeliveryPolicyFactory* factory);

				COMPONENTSYSTEM_EXPORT
				IMessageReceivePolicy* createMessageReceivePolicy(const MessageReceivePolicyDesc& desc);

				COMPONENTSYSTEM_EXPORT
				IMessageDeliveryPolicy* createMessageDeliveryPolicy(const MessageDeliveryPolicyDesc& desc);

				COMPONENTSYSTEM_EXPORT
				void destroyMessageReceivePolicy(IMessageReceivePolicy* policy);

				COMPONENTSYSTEM_EXPORT
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
#ifndef ComponentSystem_EXPORTS
		extern template class COMPONENTSYSTEM_EXPORT Singleton<MessagingPoliciesManager>;
#else
		template class COMPONENTSYSTEM_EXPORT Singleton<MessagingPoliciesManager>;
#endif
#endif

	} // namespace Core
} // namespace UnknownEngine
