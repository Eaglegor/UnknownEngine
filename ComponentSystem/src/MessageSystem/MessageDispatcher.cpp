/*
 * MessageDispatcher.cpp
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine
{
	namespace Core
	{

		typedef std::unordered_map<ComponentMessageTypeId, IMessageListener*> MessageListenersListIterator;

		MessageDispatcher::MessageDispatcher ()
		{
		}

		MessageDispatcher::~MessageDispatcher ()
		{
		}

		void MessageDispatcher::addListener ( ComponentMessageTypeId message_type_id, IMessageListener* listener )
		{

		}

		void MessageDispatcher::addListener ( std::string message_type_name, IMessageListener* listener )
		{
			ComponentMessageTypeId message_id = MessageDictionary::getSingleton()->getMessageTypeId(message_type_name);
		}

		void MessageDispatcher::removeListener ( ComponentMessageTypeId message_type_id, IMessageListener* listener )
		{
		}

		void MessageDispatcher::removeListener ( std::string message_type_name, IMessageListener* listener )
		{
		}

		void MessageDispatcher::removeListener ( IMessageListener* listener )
		{
		}

		void MessageDispatcher::deliverMessage ( Message* msg )
		{
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
