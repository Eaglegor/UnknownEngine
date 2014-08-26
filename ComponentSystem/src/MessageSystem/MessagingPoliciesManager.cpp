#include <MessageSystem/MessagingPoliciesManager.h>

#include <MessageSystem/Policies/AnyMessageReceivePolicy.h>
#include <MessageSystem/Policies/BroadcastMessageDeliverPolicy.h>
#include <MessageSystem/Policies/FromSingleSenderMessageReceivePolicy.h>
#include <MessageSystem/Policies/SingleReceiverMessageDeliverPolicy.h>
#include <Properties/Properties.h>

#define Creator(name) &MessagingPoliciesManager::name

namespace UnknownEngine
{
	namespace Core
	{

		MessagingPoliciesManager::MessagingPoliciesManager ( EngineContext* engine_context )
			: engine_context ( engine_context ), EMPTY_POLICY_TYPE ( "None" )
		{

			registerReceivePolicyCreator<AnyMessageReceivePolicy> ( Creator ( createAnyMessageReceivePolicy ) );
			registerReceivePolicyCreator<FromSingleSenderMessageReceivePolicy> ( Creator ( createFromSingleSenderMessageReceivePolicy ) );

			registerDeliveryPolicyCreator<BroadcastMessageDeliverPolicy> ( Creator ( createBroadcastMessageDeliveryPolicy ) );
			registerDeliveryPolicyCreator<SingleReceiverMessageDeliverPolicy> ( Creator ( createSingleReceieverMessageReceivePolicy ) );
		}

		IMessageReceivePolicy *MessagingPoliciesManager::createPrefabReceiveMessagePolicy ( const MessagePolicyType &type, const Properties &options )
		{
			if ( type.empty() || type == EMPTY_POLICY_TYPE ) return nullptr;
			if ( !isPrefabReceivePolicyType ( type ) ) throw UnknownPrefabPolicy ( "There is no prefab message receive policy " + type );
			ReceivePolicyPtr policy = ( this->*receive_policy_creator_methods[type] ) ( options );
			IMessageReceivePolicy* result = policy.get();
			receive_policies.push_back ( std::move ( policy ) );
			return result;
		}

		IMessageDeliveryPolicy *MessagingPoliciesManager::createPrefabDeliveryMessagePolicy ( const MessagePolicyType &type, const Properties &options )
		{
			if ( type.empty() || type == EMPTY_POLICY_TYPE ) return nullptr;
			if ( !isPrefabDeliveryPolicyType ( type ) ) throw UnknownPrefabPolicy ( "There is no prefab message delivery policy " + type );
			DeliveryPolicyPtr policy = ( this->*delivery_policy_creator_methods[type] ) ( options );
			IMessageDeliveryPolicy* result = policy.get();
			delivery_policies.push_back ( std::move ( policy ) );
			return result;
		}

		void MessagingPoliciesManager::addMessageReceivePolicy ( MessagingPoliciesManager::ReceivePolicyPtr new_policy )
		{
			receive_policies.push_back ( std::move ( new_policy ) );
		}

		void MessagingPoliciesManager::addMessageDeliveryPolicy ( MessagingPoliciesManager::DeliveryPolicyPtr new_policy )
		{
			delivery_policies.push_back ( std::move ( new_policy ) );
		}

		bool MessagingPoliciesManager::isPrefabReceivePolicyType ( const MessagePolicyType &type )
		{
			if ( type.empty() || type == EMPTY_POLICY_TYPE ) return true;
			return receive_policy_creator_methods.find ( type ) != receive_policy_creator_methods.end();
		}

		bool MessagingPoliciesManager::isPrefabDeliveryPolicyType ( const MessagePolicyType &type )
		{
			if ( type.empty() || type == EMPTY_POLICY_TYPE ) return true;
			return delivery_policy_creator_methods.find ( type ) != delivery_policy_creator_methods.end();
		}

		MessagingPoliciesManager::ReceivePolicyPtr MessagingPoliciesManager::createAnyMessageReceivePolicy ( const Properties &options )
		{
			AnyMessageReceivePolicy* policy = new AnyMessageReceivePolicy();
			return std::move ( std::unique_ptr<IMessageReceivePolicy> ( policy ) );
		}

		MessagingPoliciesManager::ReceivePolicyPtr MessagingPoliciesManager::createFromSingleSenderMessageReceivePolicy ( const Properties &options )
		{
			MessageSystemParticipantId sender_id ( options.get<std::string> ( "sender_name" ) );
			FromSingleSenderMessageReceivePolicy* policy = new FromSingleSenderMessageReceivePolicy ( sender_id );
			return std::move ( std::unique_ptr<IMessageReceivePolicy> ( policy ) );
		}

		MessagingPoliciesManager::DeliveryPolicyPtr MessagingPoliciesManager::createBroadcastMessageDeliveryPolicy ( const Properties &options )
		{
			BroadcastMessageDeliverPolicy* policy = new BroadcastMessageDeliverPolicy();
			return std::move ( std::unique_ptr<IMessageDeliveryPolicy> ( policy ) );
		}

		MessagingPoliciesManager::DeliveryPolicyPtr MessagingPoliciesManager::createSingleReceieverMessageReceivePolicy ( const Properties &options )
		{
			MessageSystemParticipantId receiver_id ( options.get<std::string> ( "receiver_name" ) );
			SingleReceiverMessageDeliverPolicy* policy = new SingleReceiverMessageDeliverPolicy ( receiver_id );
			return std::move ( std::unique_ptr<IMessageDeliveryPolicy> ( policy ) );
		}

		template <typename PolicyType>
		void MessagingPoliciesManager::registerReceivePolicyCreator ( MessagingPoliciesManager::ReceivePolicyCreator creator )
		{
			receive_policy_creator_methods[PolicyType::getType()] = creator;
		}

		template <typename PolicyType>
		void MessagingPoliciesManager::registerDeliveryPolicyCreator ( MessagingPoliciesManager::DeliveryPolicyCreator creator )
		{
			delivery_policy_creator_methods[PolicyType::getType()] = creator;
		}

	} // namespace Core
} // namespace UnknownEngine
