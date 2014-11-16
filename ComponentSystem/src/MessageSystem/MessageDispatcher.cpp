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

//#define ENABLE_CORE_SUBSYSTEM_DEBUG_LOG
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

		void MessageDispatcher::addListener ( const MessageType &message_type, IMessageListener* listener, IMessageReceivePolicy* receive_policy )
		{
			std::lock_guard<LockPrimitive> guard(lock);
			
			auto iter = listeners.find(message_type);
			if(iter == listeners.end())
			{
				iter = listeners.emplace(message_type, MessageListenersMap()).first;
			}
			MessageListenersMap &listeners_map = iter->second;
			
			RegisteredListener rlistener;
			rlistener.listener = listener;
			rlistener.receive_policy = receive_policy;
			listeners_map.insert(std::make_pair(listener->getMessageSystemParticipantId(), rlistener));
			onNewListener(message_type, listener, receive_policy);
		}

		void MessageDispatcher::removeListener ( IMessageListener* listener )
		{
			std::lock_guard<LockPrimitive> guard(lock);
			onRemoveListener(listener);
			
			for(auto &message_type_iter : listeners)
			{
				message_type_iter.second.erase(listener->getMessageSystemParticipantId());
			}
		}

		void MessageDispatcher::addSender ( const MessageType &message_type, IMessageSender* sender, IMessageDeliveryPolicy* delivery_policy )
		{
			std::lock_guard<LockPrimitive> guard(lock);
			
			auto iter = senders.find(message_type);
			if(iter == senders.end())
			{
				iter = senders.emplace(message_type, MessageSendersMap()).first;
			}
			MessageSendersMap &senders_map = iter->second;

			RegisteredSender rsender;
			rsender.sender = sender;
			rsender.delivery_policy = delivery_policy;
			senders_map.insert(std::make_pair(sender->getMessageSystemParticipantId(), rsender));
			onNewSender(message_type, sender, delivery_policy);
		}

		void MessageDispatcher::removeSender ( IMessageSender* sender )
		{
			std::lock_guard<LockPrimitive> guard(lock);
			onRemoveSender(sender);
			
			for(auto &message_type_iter : senders)
			{
				message_type_iter.second.erase(sender->getMessageSystemParticipantId());
			}
		}

		void MessageDispatcher::onNewListener (const MessageType &message_type, IMessageListener* listener, IMessageReceivePolicy* receive_policy )
		{
			auto message_type_iter = senders.find(message_type);
			if(message_type_iter == senders.end()) return;

			for(auto &iter : message_type_iter->second)
			{
				if(iter.second.delivery_policy == nullptr || iter.second.delivery_policy->allowDeliveryToListener(listener))
				{
					if(receive_policy == nullptr || receive_policy->allowReceiveFromSender(iter.second.sender))
					{
						iter.second.sender->attachListener(listener, receive_policy);
					}
				}
			}
		}

		void MessageDispatcher::onNewSender (const MessageType &message_type, IMessageSender* sender, IMessageDeliveryPolicy* delivery_policy  )
		{
			auto message_type_iter = listeners.find(message_type);
			if(message_type_iter == listeners.end()) return;
			
			for(auto &iter : message_type_iter->second)
			{
				if(delivery_policy == nullptr || delivery_policy->allowDeliveryToListener(iter.second.listener))
				{
					if(iter.second.receive_policy == nullptr || iter.second.receive_policy->allowReceiveFromSender(sender))
					{
						sender->attachListener(iter.second.listener, iter.second.receive_policy);
					}
				}
			}
		}
		
		void MessageDispatcher::onRemoveListener ( IMessageListener* listener )
		{
			for(auto &message_type_iter : senders)
			{
				for(auto &iter : message_type_iter.second)
				{
					iter.second.sender->detachListener(listener);
				}
			}
		}

		void MessageDispatcher::onRemoveSender ( IMessageSender* sender )
		{
			for(auto &message_type_iter : listeners)
			{
				for(auto &iter : message_type_iter.second)
				{
					sender->detachListener(iter.second.listener);
				}
			}
		}
		
	} /* namespace Core */
} /* namespace UnknownEngine */

