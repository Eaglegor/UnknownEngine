#pragma once
/*
 * MessageDispatcher.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <unordered_map>
#include <list>

#include <Singleton.h>
#include <NumericIdentifierType.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageDeliveryPolicy;
		class IMessageReceivePolicy;
		class IMessageListener;
		class PackedMessage;

		class MessageDispatcher : public Singleton<MessageDispatcher>
		{
			public:
				MessageDispatcher ();
				virtual ~MessageDispatcher ();

				void addListener ( NumericIdentifierType message_type_id, IMessageListener* listener, IMessageReceivePolicy* receive_policy = nullptr );
				void addListener ( std::string message_type_name, IMessageListener* listener, IMessageReceivePolicy* receive_policy = nullptr );

				void removeListener ( NumericIdentifierType message_type_id, IMessageListener* listener );
				void removeListener ( std::string message_type_name, IMessageListener* listener );
				void removeListener ( IMessageListener* listener );

				void addSniffer ( IMessageListener* listener, IMessageReceivePolicy* receive_policy );
				void removeSniffer ( IMessageListener* listener );

				void setListenerReceivePolicy( NumericIdentifierType message_type_id, IMessageListener* listener, IMessageReceivePolicy* receive_policy = nullptr );

				void deliverMessage ( const PackedMessage &msg, IMessageDeliveryPolicy* delivery_policy = nullptr ) const;

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
				typedef std::unordered_map< NumericIdentifierType, MessageListenersList > MessageListenersMap;

				const MessageListenersList* getRegisteredListeners ( NumericIdentifierType message_type_id ) const;
				MessageListenersList* getRegisteredListeners ( NumericIdentifierType message_type_id );

				MessageListenersMap listeners;

				std::list<RegisteredListener> sniffers;

				int new_listener_internal_id;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
