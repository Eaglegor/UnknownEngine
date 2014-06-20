#pragma once
/*
 * MessageDispatcher.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <unordered_map>
#include <list>

#include <MessageSystem/IMessageListener.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageDeliveryPolicy;
		class IMessageReceivePolicy;
		class PackedMessage;

		class MessageDispatcher
		{
			public:
				virtual ~MessageDispatcher ();

				void addListener ( ComponentMessageTypeId message_type_id, IMessageListener* listener, IMessageReceivePolicy* receive_policy = nullptr );
				void addListener ( std::string message_type_name, IMessageListener* listener, IMessageReceivePolicy* receive_policy = nullptr );

				void removeListener ( ComponentMessageTypeId message_type_id, IMessageListener* listener );
				void removeListener ( std::string message_type_name, IMessageListener* listener );
				void removeListener ( IMessageListener* listener );

				void addSniffer ( IMessageListener* listener, IMessageReceivePolicy* receive_policy );
				void removeSniffer ( IMessageListener* listener );

				void setListenerReceivePolicy( ComponentMessageTypeId message_type_id, IMessageListener* listener, IMessageReceivePolicy* receive_policy = nullptr );

				void deliverMessage ( const PackedMessage &msg, const IMessageDeliveryPolicy* delivery_policy = nullptr ) const;

				static MessageDispatcher* getSingleton ();
				static void initInstance(MessageDispatcher* dispatcher);

			private:

				struct RegisteredListener
				{

						RegisteredListener ( IMessageListener* listener, IMessageReceivePolicy* receive_policy )
								: listener ( listener ), receive_policy ( receive_policy )
						{

						}

						IMessageListener* listener;
						IMessageReceivePolicy* receive_policy;
				};

				typedef std::list< RegisteredListener > MessageListenersList;
				typedef std::unordered_map< ComponentMessageTypeId, MessageListenersList > MessageListenersMap;

				MessageDispatcher ();

				const MessageListenersList* getRegisteredListeners ( ComponentMessageTypeId message_type_id ) const;
				MessageListenersList* getRegisteredListeners ( ComponentMessageTypeId message_type_id );

				MessageListenersMap listeners;

				std::list<RegisteredListener> sniffers;

				int new_listener_internal_id;

				static MessageDispatcher* instance;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
