#include <stdafx.h>
#include <MessageSystem/Policies/MessagingPoliciesManager.h>

#include <MessageSystem/Policies/Listener/IMessageReceivePolicyFactory.h>
#include <MessageSystem/Policies/Listener/StandardMessageReceivePoliciesFactory.h>

#include <MessageSystem/Policies/Sender/IMessageDeliveryPolicyFactory.h>
#include <MessageSystem/Policies/Sender/StandardMessageDeliveryPoliciesFactory.h>

#include <MessageSystem/Policies/Listener/MessageReceivePolicyDesc.h>
#include <MessageSystem/Policies/Sender/MessageDeliveryPolicyDesc.h>

#include <EngineLogLevel.h>

#include <Logging.h>

namespace UnknownEngine
{
	namespace Core
	{
		
		template<>
		MessagingPoliciesManager* Singleton<MessagingPoliciesManager>::instance = nullptr;
		
		MessagingPoliciesManager::MessagingPoliciesManager():
		logger("Core.MessagingPoliciesManager", ENGINE_LOG_LEVEL)
		{
			createStandardFactoires();
		}
		
		MessagingPoliciesManager::~MessagingPoliciesManager()
		{
			destroyStandardFactoires();
		}

		
		void MessagingPoliciesManager::addMessageDeliveryPolicyFactory ( IMessageDeliveryPolicyFactory* factory )
		{
			auto iter = delivery_policy_factories.find(factory->getName());
			if(iter != delivery_policy_factories.end())
			{
				LOG_ERROR(logger, "Failed to register message delivery policy factory " + factory->getName() + ". Factory with the same name already registered");
				return;
			}
			delivery_policy_factories.emplace(factory->getName(), factory);
		}

		void MessagingPoliciesManager::addMessageReceivePolicyFactory ( IMessageReceivePolicyFactory* factory )
		{
			auto iter = receive_policy_factories.find(factory->getName());
			if(iter != receive_policy_factories.end())
			{
				LOG_ERROR(logger, "Failed to register message receive policy factory " + factory->getName() + ". Factory with the same name already registered");
				return;
			}
			receive_policy_factories.emplace(factory->getName(), factory);
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
			auto iter = delivery_policy_factories.find(factory->getName());
			if(iter == delivery_policy_factories.end())
			{
				LOG_ERROR(logger, "Can't unregister message delivery policy factory " + factory->getName() + ". Factory isn't registered");
				return;
			}
			delivery_policy_factories.erase(iter);
		}

		void MessagingPoliciesManager::removeMessageReceivePolicyFactory ( IMessageReceivePolicyFactory* factory )
		{
			auto iter = receive_policy_factories.find(factory->getName());
			if(iter == receive_policy_factories.end())
			{
				LOG_ERROR(logger, "Can't unregister message receive policy factory " + factory->getName() + ". Factory isn't registered");
				return;
			}
			receive_policy_factories.erase(iter);
		}
		
	} // namespace Core
} // namespace UnknownEngine
