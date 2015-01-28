#include <stdafx.h>

#include <MessageSystem/Policies/Sender/IMessageDeliveryPolicy.h>
#include <MessageSystem/Policies/Listener/IMessageReceivePolicy.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/IMessageSender.h>
#include <MessageSystem/Policies/Listener/MessageListenerRules.h>
#include <MessageSystem/Policies/Sender/MessageSenderRules.h>
#include <MessageSystem/Policies/Listener/MessageReceivePolicyDesc.h>
#include <MessageSystem/Policies/Sender/MessageDeliveryPolicyDesc.h>

#define ENABLE_CORE_SUBSYSTEM_ERROR_LOG
#include <Logging.h>
#include <EngineLogLevel.h>

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		MessageDispatcher* Singleton<MessageDispatcher>::instance = nullptr;

		MessageDispatcher::MessageDispatcher ():
		logger(CREATE_LOGGER("Core.Engine", ENGINE_LOG_LEVEL))
		{
		}

		MessageDispatcher::~MessageDispatcher ()
		{
			RELEASE_LOGGER(logger);
		}

		void MessageDispatcher::addListener ( const MessageType &message_type, IMessageListener* listener )
		{
			std::lock_guard<LockPrimitive> guard ( lock );

			IMessageReceivePolicy* r_policy;
			{
				ListenerRules* rules = getListenerRules ( listener->getName() );
				if ( !rules )
				{
					LOG_DEBUG( logger, "!!! Not registering listener " + listener->getName() + " because there it wasn't explicitly allowed to receive messages" );
					return;
				}
				auto iter = rules->messages.find ( message_type );
				if ( iter == rules->messages.end() )
				{
					LOG_DEBUG( logger, "!!! Not registering listener " + listener->getName() + " because there is no permissive rule for message type " + MESSAGE_TYPE_NAME ( message_type ) );
					return;
				}
				r_policy = iter->second;
			}

			auto iter = listeners.find ( message_type );
			if ( iter == listeners.end() )
			{
				iter = listeners.emplace ( message_type, MessageListenersMap() ).first;
			}
			MessageListenersMap &listeners_map = iter->second;

			RegisteredListener rlistener;
			rlistener.listener = listener;
			rlistener.receive_policy = r_policy;
			auto result = listeners_map.emplace ( listener->getName(), rlistener) ;
			if(!result.second)
			{
				LOG_ERROR(logger, "Failed to register message listener " + listener->getName());
				return;
			}
			onNewListener ( message_type, listener, r_policy );
		}

		void MessageDispatcher::removeListener ( IMessageListener* listener )
		{
			std::lock_guard<LockPrimitive> guard ( lock );
			LOG_DEBUG( logger, "Removing listener" + listener->getName() );
			onRemoveListener ( listener );

			for ( auto & message_type_iter : listeners )
			{
				message_type_iter.second.erase ( listener->getName() );
			}
		}

		void MessageDispatcher::addSender ( const MessageType &message_type, IMessageSender* sender )
		{
			std::lock_guard<LockPrimitive> guard ( lock );

			IMessageDeliveryPolicy* d_policy = nullptr;
			{
				SenderRules* rules = getSenderRules(sender->getName());
				if(!rules) {
					LOG_DEBUG( logger, "!!! Not registering sender " + sender->getName() + " because there it wasn't explicitly allowed to send messages" );
					return;
				}
				auto iter = rules->messages.find(message_type);
				if(iter == rules->messages.end()) 
				{
					LOG_DEBUG( logger, "!!! Not registering sender " + sender->getName() + " because there it wasn't explicitly allowed to send messages of type " + MESSAGE_TYPE_NAME(message_type) );
					return;
				}
				d_policy = iter->second;
			}
			
			auto iter = senders.find ( message_type );
			if ( iter == senders.end() )
			{
				iter = senders.emplace ( message_type, MessageSendersMap() ).first;
			}
			MessageSendersMap &senders_map = iter->second;

			RegisteredSender rsender;
			rsender.sender = sender;
			rsender.delivery_policy = d_policy;
			auto result = senders_map.emplace ( sender->getName(), rsender );
			if(!result.second)
			{
				LOG_ERROR(logger, "Failed to register message sender " + sender->getName());
				return;
			}
			onNewSender ( message_type, sender, d_policy );
		}

		void MessageDispatcher::removeSender ( IMessageSender* sender )
		{
			std::lock_guard<LockPrimitive> guard ( lock );
			onRemoveSender ( sender );

			LOG_DEBUG( logger, "Removing sender" + sender->getName() );

			for ( auto & message_type_iter : senders )
			{
				message_type_iter.second.erase ( sender->getName() );
			}
		}

		void MessageDispatcher::onNewListener ( const MessageType &message_type, IMessageListener* listener, IMessageReceivePolicy* receive_policy )
		{
			auto message_type_iter = senders.find ( message_type );
			if ( message_type_iter == senders.end() ) return;

			for ( auto & iter : message_type_iter->second )
			{
				if ( iter.second.delivery_policy == nullptr || iter.second.delivery_policy->allowDeliveryToListener ( listener ) )
				{
					if ( receive_policy == nullptr || receive_policy->allowReceiveFromSender ( iter.second.sender ) )
					{
						iter.second.sender->attachListener ( listener );
					}
				}
			}
		}

		void MessageDispatcher::onNewSender ( const MessageType &message_type, IMessageSender* sender, IMessageDeliveryPolicy* delivery_policy )
		{
			auto message_type_iter = listeners.find ( message_type );
			if ( message_type_iter == listeners.end() ) {
				return;
			}

			for ( auto & iter : message_type_iter->second )
			{
				if ( delivery_policy == nullptr || delivery_policy->allowDeliveryToListener ( iter.second.listener ) )
				{
					if ( iter.second.receive_policy == nullptr || iter.second.receive_policy->allowReceiveFromSender ( sender ) )
					{
						sender->attachListener ( iter.second.listener );
					}
				}
			}
		}

		void MessageDispatcher::onRemoveListener ( IMessageListener* listener )
		{
			for ( auto & message_type_iter : senders )
			{
				for ( auto & iter : message_type_iter.second )
				{
					iter.second.sender->detachListener ( listener );
				}
			}
		}

		void MessageDispatcher::onRemoveSender ( IMessageSender* sender )
		{
			sender->detachAllListeners();
		}

		void MessageDispatcher::setListenerRules ( const char* listener_name, const UnknownEngine::Core::MessageListenerRules& listener_rules )
		{
			ListenerRules *rules = createListenerRules ( listener_name );

			for ( const MessageListenerRule & rule : listener_rules )
			{
				MessageReceivePolicyDesc desc;
				desc.type = rule.receive_policy_type_name;
				desc.options = rule.receive_policy_options;
				rules->messages[MESSAGE_TYPE_ID(rule.message_type_name)] = MessagingPoliciesManager::getSingleton()->createMessageReceivePolicy(desc);
			}
		}

		void MessageDispatcher::setSenderRules ( const char* sender_name, const UnknownEngine::Core::MessageSenderRules& listener_rules )
		{
			SenderRules *rules = createSenderRules ( sender_name );

			for ( const MessageSenderRule & rule : listener_rules )
			{
				MessageDeliveryPolicyDesc desc;
				desc.type = rule.delivery_policy_type_name;
				desc.options = rule.delivery_policy_options;
				rules->messages[MESSAGE_TYPE_ID(rule.message_type_name)] = MessagingPoliciesManager::getSingleton()->createMessageDeliveryPolicy(desc);
			}
		}

		void MessageDispatcher::clearListenerRules ( const char* listener_name )
		{
			for (auto &iter : listener_rules[listener_name].messages)
			{
				if (iter.second != nullptr) MessagingPoliciesManager::getSingleton()->destroyMessageReceivePolicy(iter.second);
			}
			listener_rules.erase ( listener_name );
		}

		void MessageDispatcher::clearSenderRules ( const char* sender_name )
		{
			for (auto &iter : sender_rules[sender_name].messages)
			{
				if (iter.second != nullptr) MessagingPoliciesManager::getSingleton()->destroyMessageDeliveryPolicy(iter.second);
			}
			sender_rules.erase ( sender_name );
		}

		MessageDispatcher::ListenerRules* MessageDispatcher::createListenerRules ( const std::string& id )
		{
			auto val = &listener_rules.emplace ( id, ListenerRules() ).first->second;
			val->messages.clear();
			return val;
		}

		MessageDispatcher::SenderRules* MessageDispatcher::createSenderRules ( const std::string& id )
		{
			auto val = &sender_rules.emplace ( id, SenderRules() ).first->second;
			val->messages.clear();
			return val;
		}

		MessageDispatcher::ListenerRules* MessageDispatcher::getListenerRules ( const std::string& id )
		{
			auto rules_entry = listener_rules.find ( id );
			if ( rules_entry == listener_rules.end() ) return nullptr;
			return &rules_entry->second;
		}

		MessageDispatcher::SenderRules* MessageDispatcher::getSenderRules ( const std::string& id )
		{
			auto rules_entry = sender_rules.find ( id );
			if ( rules_entry == sender_rules.end() ) return nullptr;
			return &rules_entry->second;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */

