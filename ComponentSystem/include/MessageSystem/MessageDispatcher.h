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
#include <MessageSystem/PackedMessage.h>
#include <Singleton.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageDeliveryPolicy;
		class IMessageReceivePolicy;

		class MessageDispatcher : public Singleton<MessageDispatcher>
		{
			public:
				MessageDispatcher ();
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

				const MessageListenersList* getRegisteredListeners ( ComponentMessageTypeId message_type_id ) const;
				MessageListenersList* getRegisteredListeners ( ComponentMessageTypeId message_type_id );

				MessageListenersMap listeners;

				std::list<RegisteredListener> sniffers;

				int new_listener_internal_id;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
