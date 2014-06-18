#pragma once
/*
 * MessageDispatcher.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <unordered_map>
#include <list>

#include <MessageSystem/Message.h>
#include <MessageSystem/IMessageListener.h>

namespace UnknownEngine
{
	namespace Core
	{

		typedef std::list<IMessageListener*> MessageListenersList;
		typedef std::unordered_map<ComponentMessageTypeId, MessageListenersList> MessageListenersMap;

		class MessageDispatcher
		{
			public:
				virtual ~MessageDispatcher ();

				void addListener ( ComponentMessageTypeId message_type_id, IMessageListener* listener );
				void addListener ( std::string message_type_name, IMessageListener* listener );

				void removeListener ( ComponentMessageTypeId message_type_id, IMessageListener* listener );
				void removeListener ( std::string message_type_name, IMessageListener* listener );
				void removeListener ( IMessageListener* listener );

				void deliverMessage ( const Message &msg ) const;

				static MessageDispatcher* getSingleton ();

			private:

				MessageDispatcher ();

				const MessageListenersList* getRegisteredListeners ( ComponentMessageTypeId message_type_id ) const;
				MessageListenersList* getRegisteredListeners ( ComponentMessageTypeId message_type_id );

				MessageListenersMap listeners;

				static MessageDispatcher* instance;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
