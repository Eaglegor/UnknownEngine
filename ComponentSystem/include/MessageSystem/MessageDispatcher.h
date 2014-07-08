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
#include <MessageSystem/MessageType.h>
#include <Dictionary.h>

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

				void addListener ( const MessageType &message_type_id, IMessageListener* listener, IMessageReceivePolicy* receive_policy = nullptr );
				void addListener ( const std::string &message_type_name, IMessageListener* listener, IMessageReceivePolicy* receive_policy = nullptr );

				void removeListener ( const MessageType &message_type_id, IMessageListener* listener );
				void removeListener ( const std::string &message_type_name, IMessageListener* listener );
				void removeListener ( IMessageListener* listener );

				void addSniffer ( IMessageListener* listener, IMessageReceivePolicy* receive_policy );
				void removeSniffer ( IMessageListener* listener );

				void setListenerReceivePolicy( const MessageType &message_type_id, IMessageListener* listener, IMessageReceivePolicy* receive_policy);
				void setListenerReceivePolicy( const std::string &message_type_name, IMessageListener* listener, IMessageReceivePolicy* receive_policy);

				void deliverMessage ( const PackedMessage &msg, IMessageDeliveryPolicy* delivery_policy = nullptr ) const;

			private:

				struct RegisteredListener
				{
						RegisteredListener ( IMessageListener* listener, IMessageReceivePolicy* receive_policy )
							: listener ( listener ), receive_policy ( receive_policy ){}

						IMessageListener* listener;
						IMessageReceivePolicy* receive_policy;
				};

				typedef std::list< RegisteredListener > MessageListenersList;
				typedef std::unordered_map< MessageType, MessageListenersList > MessageListenersMap;

				const MessageListenersList* getRegisteredListeners ( const MessageType &message_type_id ) const;
				MessageListenersList* getRegisteredListeners ( const MessageType &message_type_id );

				MessageListenersMap listeners;
				MessageListenersList sniffers;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
