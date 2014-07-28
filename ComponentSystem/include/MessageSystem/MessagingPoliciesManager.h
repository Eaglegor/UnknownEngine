#pragma once

#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>
#include <Exception.h>
#include <MessageSystem/Policies/MessagePolicyType.h>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>
#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>

namespace UnknownEngine {
	namespace Core {

		class Properties;
		class EngineContext;

		class MessagingPoliciesManager
		{
			public:
				UNKNOWNENGINE_SIMPLE_EXCEPTION(UnknownPrefabPolicy);
				typedef std::unique_ptr <IMessageReceivePolicy> ReceivePolicyPtr;
				typedef std::unique_ptr <IMessageDeliveryPolicy> DeliveryPolicyPtr;

				MessagingPoliciesManager(EngineContext *engine_context);

				IMessageReceivePolicy* createPrefabReceiveMessagePolicy(const MessagePolicyType &type, const Properties& options);
				IMessageDeliveryPolicy* createPrefabDeliveryMessagePolicy(const MessagePolicyType &type, const Properties& options);

				void addMessageReceivePolicy(ReceivePolicyPtr new_policy);
				void addMessageDeliveryPolicy(DeliveryPolicyPtr new_policy);

				bool isPrefabReceivePolicyType(const MessagePolicyType& type);
				bool isPrefabDeliveryPolicyType(const MessagePolicyType& type);

			private:
				std::vector<ReceivePolicyPtr> receive_policies;
				std::vector<DeliveryPolicyPtr> delivery_policies;

				const MessagePolicyType EMPTY_POLICY_TYPE;

				typedef ReceivePolicyPtr&& (MessagingPoliciesManager::*ReceivePolicyCreator)(const Properties&);
				typedef DeliveryPolicyPtr&& (MessagingPoliciesManager::*DeliveryPolicyCreator)(const Properties&);

				ReceivePolicyPtr&& createAnyMessageReceivePolicy(const Properties& options);
				ReceivePolicyPtr&& createFromSingleSenderMessageReceivePolicy(const Properties& options);

				DeliveryPolicyPtr&& createBroadcastMessageDeliveryPolicy(const Properties& options);
				DeliveryPolicyPtr&& createSingleReceieverMessageReceivePolicy(const Properties& options);

				template <typename PolicyType>
				void registerReceivePolicyCreator(ReceivePolicyCreator creator);

				template <typename PolicyType>
				void registerDeliveryPolicyCreator(DeliveryPolicyCreator creator);

				std::unordered_map<MessagePolicyType, ReceivePolicyCreator> receive_policy_creator_methods;
				std::unordered_map<MessagePolicyType, DeliveryPolicyCreator> delivery_policy_creator_methods;

				EngineContext* engine_context;

		};

	} // namespace Core
} // namespace UnknownEngine
