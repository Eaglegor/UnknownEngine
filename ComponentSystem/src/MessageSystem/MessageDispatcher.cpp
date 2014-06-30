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

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		MessageDispatcher* Singleton<MessageDispatcher>::instance = nullptr;

		MessageDispatcher::MessageDispatcher ()
				: new_listener_internal_id ( 0 )
		{
		}

		MessageDispatcher::~MessageDispatcher ()
		{
		}

		void MessageDispatcher::addListener ( NumericIdentifierType message_type_id, IMessageListener* listener, IMessageReceivePolicy* receive_policy )
		{

			if ( message_type_id == INVALID_NUMERIC_IDENTIFIER ) return;

			RegisteredListener new_listener ( listener, receive_policy );

			MessageListenersList* existing_list = getRegisteredListeners ( message_type_id );
			if ( existing_list == nullptr )
			{
				MessageListenersList new_list;
				new_list.push_back ( new_listener );
				listeners.insert ( std::make_pair ( message_type_id, new_list ) );
			}
			else
			{
				existing_list->push_back ( new_listener );
			}
		}

		void MessageDispatcher::addListener ( std::string message_type_name, IMessageListener* listener, IMessageReceivePolicy* receive_policy )
		{
			NumericIdentifierType message_type_id = MessageDictionary::getSingleton ()->getMessageTypeId ( message_type_name );
			addListener ( message_type_id, listener );
		}

		void MessageDispatcher::removeListener ( NumericIdentifierType message_type_id, IMessageListener* listener )
		{
			if ( listener == nullptr ) return;
			MessageListenersList* registered_listeners = getRegisteredListeners ( message_type_id );
			if ( registered_listeners != nullptr )
			{
				MessageListenersList::iterator iter = registered_listeners->begin ();
				while ( iter != registered_listeners->end () )
				{
					if ( *iter->listener == *listener ) iter = registered_listeners->erase ( iter );
					else ++iter;
				}
			}
		}

		void MessageDispatcher::removeListener ( std::string message_type_name, IMessageListener* listener )
		{
			NumericIdentifierType message_type_id = MessageDictionary::getSingleton ()->getMessageTypeId ( message_type_name );
			removeListener ( message_type_id, listener );
		}

		void MessageDispatcher::removeListener ( IMessageListener* listener )
		{
			MessageListenersMap::iterator iter = listeners.begin ();
			while ( iter != listeners.end () )
			{
				removeListener ( iter->first, listener );
				++iter;
			}
		}

		void MessageDispatcher::setListenerReceivePolicy ( NumericIdentifierType message_type_id, IMessageListener* listener, IMessageReceivePolicy* receive_policy )
		{
			if ( listener == nullptr ) return;
			MessageListenersList* registered_listeners = getRegisteredListeners ( message_type_id );
			if ( registered_listeners != nullptr )
			{
				MessageListenersList::iterator iter = registered_listeners->begin ();
				while ( iter != registered_listeners->end () )
				{
					if ( *iter->listener == *listener ) iter->receive_policy = receive_policy;
					++iter;
				}
			}
		}

		void MessageDispatcher::deliverMessage ( const PackedMessage &msg, IMessageDeliveryPolicy* delivery_policy ) const
		{
			const MessageListenersList* list = getRegisteredListeners ( msg.getMessageTypeId () );
			if ( list != nullptr )
			{
				for ( RegisteredListener registered_listener : *list )
				{
					if ( delivery_policy == nullptr || delivery_policy->allowDeliveryToListener ( registered_listener.listener ) )
					{
						if ( registered_listener.receive_policy == nullptr || registered_listener.receive_policy->acceptMessage ( msg ) )
						{
							registered_listener.listener->processMessage ( msg );
							delivery_policy->notifyDelivered();
						}
					}
				}
			}
		}

		const MessageDispatcher::MessageListenersList* MessageDispatcher::getRegisteredListeners ( NumericIdentifierType message_type_id ) const
		{
			MessageListenersMap::const_iterator existing_list = listeners.find ( message_type_id );
			if ( existing_list == listeners.end () ) return nullptr;
			return &existing_list->second;
		}

		MessageDispatcher::MessageListenersList* MessageDispatcher::getRegisteredListeners ( NumericIdentifierType message_type_id )
		{
			MessageListenersMap::iterator existing_list = listeners.find ( message_type_id );
			if ( existing_list == listeners.end () ) return nullptr;
			return &existing_list->second;
		}

		void MessageDispatcher::addSniffer ( IMessageListener* listener, IMessageReceivePolicy* receive_policy )
		{
			RegisteredListener new_listener ( listener, receive_policy );
			sniffers.push_back ( new_listener );
		}

		void MessageDispatcher::removeSniffer ( IMessageListener* listener )
		{
			MessageListenersList::iterator iter = sniffers.begin ();
			while ( iter != sniffers.end () )
			{
				if ( *iter->listener == *listener ) iter = sniffers.erase ( iter );
				else ++iter;
			}
		}

	} /* namespace Core */
} /* namespace UnknownEngine */

