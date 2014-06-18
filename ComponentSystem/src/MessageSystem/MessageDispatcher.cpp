/*
 * MessageDispatcher.cpp
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine
{
	namespace Core
	{

		MessageDispatcher* MessageDispatcher::instance = nullptr;

		MessageDispatcher::MessageDispatcher ()
		{
		}

		MessageDispatcher::~MessageDispatcher ()
		{
		}

		void MessageDispatcher::addListener ( ComponentMessageTypeId message_type_id, IMessageListener* listener )
		{

			if ( message_type_id == UNKNOWN_MESSAGE_TYPE ) return;

			MessageListenersList* existing_list = getRegisteredListeners( message_type_id );
			if ( existing_list == nullptr )
			{
				MessageListenersList new_list;
				new_list.push_back( listener );
				listeners.insert( std::make_pair( message_type_id, new_list ) );
			}
			else
			{
				existing_list->push_back( listener );
			}
		}

		void MessageDispatcher::addListener ( std::string message_type_name, IMessageListener* listener )
		{
			ComponentMessageTypeId message_type_id = MessageDictionary::getSingleton()->getMessageTypeId( message_type_name );
			addListener( message_type_id, listener );
		}

		void MessageDispatcher::removeListener ( ComponentMessageTypeId message_type_id, IMessageListener* listener )
		{
			if ( listener == nullptr ) return;
			MessageListenersList* registered_listeners = getRegisteredListeners( message_type_id );
			if ( registered_listeners != nullptr )
			{
				MessageListenersList::iterator iter = registered_listeners->begin();
				while ( iter != registered_listeners->end() )
				{
					if ( ( *( *iter ) ) == ( *listener ) ) iter = registered_listeners->erase( iter );
					else ++iter;
				}
			}
		}

		void MessageDispatcher::removeListener ( std::string message_type_name, IMessageListener* listener )
		{
			ComponentMessageTypeId message_type_id = MessageDictionary::getSingleton()->getMessageTypeId( message_type_name );
			removeListener( message_type_id, listener );
		}

		void MessageDispatcher::removeListener ( IMessageListener* listener )
		{
			MessageListenersMap::iterator iter = listeners.begin();
			while ( iter != listeners.end() )
			{
				removeListener( iter->first, listener );
				++iter;
			}
		}

		void MessageDispatcher::deliverMessage ( const Message &msg ) const
		{
			const MessageListenersList* list = getRegisteredListeners( msg.getTypeId() );
			if ( list != nullptr )
			{
				for ( IMessageListener* listener : *list )
				{
					if ( msg.getDeliveryPolicy() == nullptr || msg.getDeliveryPolicy()->allowDeliverToListener( listener ) )
					{
						if ( listener->getMessageReceivePolicy() == nullptr || listener->getMessageReceivePolicy()->acceptMessage( msg ) )
						{
							listener->processMessage( msg );
						}
					}
				}
			}
		}

		const MessageListenersList* MessageDispatcher::getRegisteredListeners ( ComponentMessageTypeId message_type_id ) const
		{
			MessageListenersMap::const_iterator existing_list = listeners.find( message_type_id );
			if ( existing_list == listeners.end() ) return nullptr;
			return &existing_list->second;
		}

		MessageListenersList* MessageDispatcher::getRegisteredListeners ( ComponentMessageTypeId message_type_id )
		{
			MessageListenersMap::iterator existing_list = listeners.find( message_type_id );
			if ( existing_list == listeners.end() ) return nullptr;
			return &existing_list->second;
		}

		MessageDispatcher* MessageDispatcher::getSingleton ()
		{
			if ( instance == nullptr )
			{
				instance = new MessageDispatcher();
			}
			return instance;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
