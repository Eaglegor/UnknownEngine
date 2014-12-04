/*
 * MessageDispatcher.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <stdafx.h>

#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/IMessageSender.h>
#include <MessageSystem/MessageListenerRules.h>
#include <MessageSystem/MessageSenderRules.h>
#include <MessageSystem/MessageReceivePolicyDesc.h>
#include <MessageSystem/MessageDeliveryPolicyDesc.h>

#define ENABLE_CORE_SUBSYSTEM_ERROR_LOG
#include <CoreLogging.h>

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		MessageDispatcher* Singleton<MessageDispatcher>::instance = nullptr;

		MessageDispatcher::MessageDispatcher ()
		{
		}

		MessageDispatcher::~MessageDispatcher ()
		{
		}

		void MessageDispatcher::addListener ( const MessageType& message_type, IMessageListener* listener, const MessageListenerRule& listener_rule )
		{
			setSingleListenerRule ( listener->getMessageSystemParticipantId(), message_type, listener_rule );
			addListener ( message_type, listener );
		}

		void MessageDispatcher::addListener ( const MessageType &message_type, IMessageListener* listener )
		{
			std::lock_guard<LockPrimitive> guard ( lock );

			IMessageReceivePolicy* r_policy;
			{
				ListenerRules* rules = getListenerRules ( listener->getMessageSystemParticipantId() );
				if ( !rules )
				{
					CORE_SUBSYSTEM_DEBUG ( "!!! Not registering listener " + listener->getName() + " because there it wasn't explicitly allowed to receive messages" );
					return;
				}
				auto iter = rules->messages.find ( message_type );
				if ( iter == rules->messages.end() )
				{
					CORE_SUBSYSTEM_DEBUG ( "!!! Not registering listener " + listener->getName() + " because there is no permissive rule for message type " + MESSAGE_TYPE_NAME ( message_type ) );
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
			auto result = listeners_map.insert ( std::make_pair ( listener->getMessageSystemParticipantId(), rlistener ) );
			if(!result.second) throw ListenerNotAddedException("Listener wasn't added to message dispatcher for some reason");
			onNewListener ( message_type, listener, r_policy );
		}

		void MessageDispatcher::removeListener ( IMessageListener* listener )
		{
			std::lock_guard<LockPrimitive> guard ( lock );
			CORE_SUBSYSTEM_DEBUG ( "Removing listener" + listener->getName() );
			onRemoveListener ( listener );

			for ( auto & message_type_iter : listeners )
			{
				message_type_iter.second.erase ( listener->getMessageSystemParticipantId() );
			}
		}

		void MessageDispatcher::addSender ( const MessageType& message_type, IMessageSender* sender, const MessageSenderRule& sender_rule )
		{
			setSingleSenderRule ( sender->getMessageSystemParticipantId(), message_type, sender_rule );
			addSender ( message_type, sender );
		}

		void MessageDispatcher::addSender ( const MessageType &message_type, IMessageSender* sender )
		{
			std::lock_guard<LockPrimitive> guard ( lock );

			IMessageDeliveryPolicy* d_policy = nullptr;
			{
				SenderRules* rules = getSenderRules(sender->getMessageSystemParticipantId());
				if(!rules) {
					CORE_SUBSYSTEM_DEBUG ( "!!! Not registering sender " + sender->getName() + " because there it wasn't explicitly allowed to send messages" );
					return;
				}
				auto iter = rules->messages.find(message_type);
				if(iter == rules->messages.end()) 
				{
					CORE_SUBSYSTEM_DEBUG ( "!!! Not registering sender " + sender->getName() + " because there it wasn't explicitly allowed to send messages of type " + MESSAGE_TYPE_NAME(message_type) );
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
			auto result = senders_map.insert ( std::make_pair ( sender->getMessageSystemParticipantId(), rsender ) );
			if(!result.second) throw SenderNotAddedException("Sender wasn't added to message dispatcher for some reason");
			onNewSender ( message_type, sender, d_policy );
		}

		void MessageDispatcher::removeSender ( IMessageSender* sender )
		{
			std::lock_guard<LockPrimitive> guard ( lock );
			onRemoveSender ( sender );

			CORE_SUBSYSTEM_DEBUG ( "Removing sender" + sender->getName() );

			for ( auto & message_type_iter : senders )
			{
				message_type_iter.second.erase ( sender->getMessageSystemParticipantId() );
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
						iter.second.sender->attachListener ( listener, receive_policy );
					}
				}
			}
		}

		void MessageDispatcher::onNewSender ( const MessageType &message_type, IMessageSender* sender, IMessageDeliveryPolicy* delivery_policy )
		{
			auto message_type_iter = listeners.find ( message_type );
			if ( message_type_iter == listeners.end() ) return;

			for ( auto & iter : message_type_iter->second )
			{
				if ( delivery_policy == nullptr || delivery_policy->allowDeliveryToListener ( iter.second.listener ) )
				{
					if ( iter.second.receive_policy == nullptr || iter.second.receive_policy->allowReceiveFromSender ( sender ) )
					{
						sender->attachListener ( iter.second.listener, iter.second.receive_policy );
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

		void MessageDispatcher::setListenerRules ( const MessageSystemParticipantId& listener_id, const MessageListenerRules& new_listener_rules )
		{
			ListenerRules *rules = createListenerRules ( listener_id );

			for ( const MessageListenerRule & rule : new_listener_rules )
			{
				MessageReceivePolicyDesc desc;
				desc.type = rule.receive_policy_type_name;
				desc.options = rule.receive_policy_options;
				rules->messages[MESSAGE_TYPE_ID(rule.message_type_name)] = MessagingPoliciesManager::getSingleton()->createMessageReceivePolicy(desc);
			}
		}

		void MessageDispatcher::setSenderRules ( const MessageSystemParticipantId& sender_id, const MessageSenderRules& new_sender_rules )
		{
			SenderRules *rules = createSenderRules ( sender_id );

			for ( const MessageSenderRule & rule : new_sender_rules )
			{
				MessageDeliveryPolicyDesc desc;
				desc.type = rule.delivery_policy_type_name;
				desc.options = rule.delivery_policy_options;
				rules->messages[MESSAGE_TYPE_ID(rule.message_type_name)] = MessagingPoliciesManager::getSingleton()->createMessageDeliveryPolicy(desc);
			}
		}

		void MessageDispatcher::clearListenerRules ( const MessageSystemParticipantId& listener_id )
		{
			for (auto &iter : listener_rules[listener_id].messages)
			{
				if (iter.second != nullptr) MessagingPoliciesManager::getSingleton()->destroyMessageReceivePolicy(iter.second);
			}
			listener_rules.erase ( listener_id );
		}

		void MessageDispatcher::clearSenderRules ( const MessageSystemParticipantId& sender_id )
		{
			for (auto &iter : sender_rules[sender_id].messages)
			{
				if (iter.second != nullptr) MessagingPoliciesManager::getSingleton()->destroyMessageDeliveryPolicy(iter.second);
			}
			sender_rules.erase ( sender_id );
		}

		MessageDispatcher::ListenerRules* MessageDispatcher::createListenerRules ( const MessageSystemParticipantId& id )
		{
			auto val = &listener_rules.emplace ( id, ListenerRules() ).first->second;
			val->messages.clear();
			return val;
		}

		MessageDispatcher::SenderRules* MessageDispatcher::createSenderRules ( const MessageSystemParticipantId& id )
		{
			auto val = &sender_rules.emplace ( id, SenderRules() ).first->second;
			val->messages.clear();
			return val;
		}

		MessageDispatcher::ListenerRules* MessageDispatcher::getListenerRules ( const MessageSystemParticipantId& id )
		{
			auto rules_entry = listener_rules.find ( id );
			if ( rules_entry == listener_rules.end() ) return nullptr;
			return &rules_entry->second;
		}

		MessageDispatcher::SenderRules* MessageDispatcher::getSenderRules ( const MessageSystemParticipantId& id )
		{
			auto rules_entry = sender_rules.find ( id );
			if ( rules_entry == sender_rules.end() ) return nullptr;
			return &rules_entry->second;
		}

		void MessageDispatcher::setSingleSenderRule ( const MessageSystemParticipantId& id, const MessageType& message_type, const MessageSenderRule& sender_rule )
		{
			SenderRules* rules = getSenderRules ( id );
			if ( rules == nullptr )
			{
				rules = createSenderRules ( id );
			}
			MessageDeliveryPolicyDesc desc;
			desc.type = sender_rule.delivery_policy_type_name;
			desc.options = sender_rule.delivery_policy_options;
			rules->messages[message_type] = MessagingPoliciesManager::getSingleton()->createMessageDeliveryPolicy(desc);
		}


		void MessageDispatcher::setSingleListenerRule ( const MessageSystemParticipantId& id, const MessageType& message_type, const MessageListenerRule& listener_rule )
		{
			ListenerRules* rules = getListenerRules ( id );
			if ( rules == nullptr )
			{
				rules = createListenerRules ( id );
			}
			MessageReceivePolicyDesc desc;
			desc.type = listener_rule.receive_policy_type_name;
			desc.options = listener_rule.receive_policy_options;
			rules->messages[message_type] = MessagingPoliciesManager::getSingleton()->createMessageReceivePolicy(desc);
		}


	} /* namespace Core */
} /* namespace UnknownEngine */

