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

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageReceivePolicyFactory;
		class IMessageDeliveryPolicyFactory;

		typedef std::string MessageReceivePolicyType;
		typedef std::string MessageDeliveryPolicyType;

		struct MessageReceivePolicyDesc
		{
			MessageReceivePolicyType type;
			Properties options;
		};

		struct MessageDeliveryPolicyDesc
		{
			MessageDeliveryPolicyType type;
			Properties options;
		};


		class EngineContext;

		class MessagingPoliciesManager : public Singleton<MessagingPoliciesManager>
		{
			public:
				COMPONENTSYSTEM_EXPORT
				void addMessageReceivePolicyFactory(IMessageReceivePolicyFactory* factory);

				COMPONENTSYSTEM_EXPORT
				void addMessageDeliveryPolicyFactory(IMessageDeliveryPolicyFactory* factory);

				COMPONENTSYSTEM_EXPORT
				void removeMessageReceivePolicyFactory(IMessageReceivePolicy* factory);

				COMPONENTSYSTEM_EXPORT
				void removeMessageDeliveryPolicyFactory(IMessageDeliveryPolicy* factory);

				COMPONENTSYSTEM_EXPORT
				IMessageReceivePolicy* createMessageReceivePolicy(const MessageReceivePolicyDesc& desc);

				COMPONENTSYSTEM_EXPORT
				IMessageDeliveryPolicy* createMessageDeliveryPolicy(const MessageDeliveryPolicyDesc &desc);

				COMPONENTSYSTEM_EXPORT
				void destroyMessageReceivePolicy(IMessageReceivePolicy* policy);

				COMPONENTSYSTEM_EXPORT
				void destroyMessageDeliveryPolicy(IMessageDeliveryPolicy* policy);

			private:
				IMessageReceivePolicyFactory* findReceivePolicyFactory(const MessageReceivePolicyType& type);
				IMessageReceivePolicyFactory* findDeliveryPolicyFactory(const MessageReceivePolicyType& type);

				void registerStandardFactoires();

				std::unordered_map<NumericIdentifierType, IMessageReceivePolicyFactory*> receive_policy_factories;
				std::unordered_map<NumericIdentifierType, IMessageDeliveryPolicyFactory*> delivery_policy_factories;
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
