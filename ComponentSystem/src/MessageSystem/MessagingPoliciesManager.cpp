#include <stdafx.h>
#include <MessageSystem/MessagingPoliciesManager.h>

#include <MessageSystem/Policies/AnyMessageReceivePolicy.h>
#include <MessageSystem/Policies/BroadcastMessageDeliverPolicy.h>
#include <MessageSystem/Policies/FromSingleSenderMessageReceivePolicy.h>
#include <MessageSystem/Policies/SingleReceiverMessageDeliverPolicy.h>
#include <MessageSystem/IMessageReceivePolicyFactory.h>
#include <MessageSystem/IMessageDeliveryPolicyFactory.h>
#include <MessageSystem/StandardMessageDeliveryPoliciesFactory.h>
#include <MessageSystem/StandardMessageReceivePoliciesFactory.h>
#include <Properties/Properties.h>

namespace UnknownEngine
{
	namespace Core
	{
		
		template<>
		MessagingPoliciesManager* Singleton<MessagingPoliciesManager>::instance = nullptr;
		
		MessagingPoliciesManager::MessagingPoliciesManager():
		internal_dictionary("MessagingPoliciesManager.Dictionary", NUMERIC_IDENTIFIER_INITIAL_VALUE, INVALID_NUMERIC_IDENTIFIER)
		{
			createStandardFactoires();
		}
		
		MessagingPoliciesManager::~MessagingPoliciesManager()
		{
			destroyStandardFactoires();
		}

		
		void MessagingPoliciesManager::addMessageDeliveryPolicyFactory ( IMessageDeliveryPolicyFactory* factory )
		{
			if ( factory->getInternalId() != INVALID_NUMERIC_IDENTIFIER ) return;

			NumericIdentifierType new_id = internal_dictionary.registerNewValue ( factory->getName() );
			factory->setInternalId ( new_id );
			delivery_policy_factories.insert ( std::make_pair ( new_id, factory ) );
		}

		void MessagingPoliciesManager::addMessageReceivePolicyFactory ( IMessageReceivePolicyFactory* factory )
		{
			if ( factory->getInternalId() != INVALID_NUMERIC_IDENTIFIER ) return;

			NumericIdentifierType new_id = internal_dictionary.registerNewValue ( factory->getName() );
			factory->setInternalId ( new_id );
			receive_policy_factories.insert ( std::make_pair ( new_id, factory ) );
		}

		IMessageDeliveryPolicy* MessagingPoliciesManager::createMessageDeliveryPolicy ( const MessageDeliveryPolicyDesc& desc )
		{
			IMessageDeliveryPolicyFactory* factory = findDeliveryPolicyFactory(desc.type);
			if(factory == nullptr) return nullptr;
			return factory->createObject(desc);
		}
		
		IMessageReceivePolicy* MessagingPoliciesManager::createMessageReceivePolicy ( const MessageReceivePolicyDesc& desc )
		{
			IMessageReceivePolicyFactory* factory = findReceivePolicyFactory(desc.type);
			if(factory == nullptr) return nullptr;
			return factory->createObject(desc);
		}

		void MessagingPoliciesManager::destroyMessageDeliveryPolicy ( IMessageDeliveryPolicy* policy )
		{
			IMessageDeliveryPolicyFactory* factory = findDeliveryPolicyFactory(policy->getType());
			if(factory == nullptr) return;
			factory->destroyObject(policy);
		}

		void MessagingPoliciesManager::destroyMessageReceivePolicy ( IMessageReceivePolicy* policy )
		{
			IMessageReceivePolicyFactory* factory = findReceivePolicyFactory(policy->getType());
			if(factory == nullptr) return;
			factory->destroyObject(policy);
		}

		IMessageDeliveryPolicyFactory* MessagingPoliciesManager::findDeliveryPolicyFactory ( const MessageDeliveryPolicyType& type )
		{
			for(auto &iter : delivery_policy_factories)
			{
				if(iter.second->supportsType(type))
				{
					return iter.second;
				}
			}
			return nullptr;
		}

		IMessageReceivePolicyFactory* MessagingPoliciesManager::findReceivePolicyFactory ( const MessageReceivePolicyType& type )
		{
			for(auto &iter : receive_policy_factories)
			{
				if(iter.second->supportsType(type))
				{
					return iter.second;
				}
			}
			return nullptr;
		}

		void MessagingPoliciesManager::createStandardFactoires()
		{
			standard_receive_policy_factory = new StandardMessageReceivePoliciesFactory();
			standard_delivery_policy_factory = new StandardMessageDeliveryPoliciesFactory();
			
			addMessageReceivePolicyFactory(standard_receive_policy_factory);
			addMessageDeliveryPolicyFactory(standard_delivery_policy_factory);
		}

		void MessagingPoliciesManager::destroyStandardFactoires()
		{
			removeMessageDeliveryPolicyFactory(standard_delivery_policy_factory);
			removeMessageReceivePolicyFactory(standard_receive_policy_factory);
			
			delete standard_delivery_policy_factory;
			delete standard_receive_policy_factory;
		}
		
		void MessagingPoliciesManager::removeMessageDeliveryPolicyFactory ( IMessageDeliveryPolicyFactory* factory )
		{
			if ( factory->getInternalId() == INVALID_NUMERIC_IDENTIFIER ) return;
			delivery_policy_factories.erase ( factory->getInternalId() );
			internal_dictionary.deleteEntryByKey ( factory->getInternalId() );
			factory->setInternalId ( INVALID_NUMERIC_IDENTIFIER );
		}

		void MessagingPoliciesManager::removeMessageReceivePolicyFactory ( IMessageReceivePolicyFactory* factory )
		{
			if ( factory->getInternalId() == INVALID_NUMERIC_IDENTIFIER ) return;
			receive_policy_factories.erase ( factory->getInternalId() );
			internal_dictionary.deleteEntryByKey ( factory->getInternalId() );
			factory->setInternalId ( INVALID_NUMERIC_IDENTIFIER );
		}
		
	} // namespace Core
} // namespace UnknownEngine
