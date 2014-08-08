#pragma once
/*
 * MessageDispatcher.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <ComponentSystem_export.h>
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

		/**

		###Concept
		Message dispatcher is responsible for delivering messages sent from subsystems/components.
		It works with generalized \ref PackedMessage "packed messages". Listeners that will receive a
		message are determined by a combination of policies (\ref IMessageReceivePolicy "receive policy"
		for listeners and \ref IDeliveryPolicy "delivery policy" for senders).

		###Usage
		If some subsystem/component wants to receive messages it registers a \ref IMessageListener "message listener"
		at the message dispatcher calling addListener() method. It can pass a \ref IMessageReceivePolicy "message receive policy"
		to specify which messages it wants to receive (e.g. from specific sender or under specific circumstances).
		If no policy is specified all messages of specified type are passed to a listener. Receive policy is saved
		for each pair (Message type, Message listener), so if single listener is able to catch different message types,
		it's receive policy may be different for each message type.

		When an event occurs at some component/subsystem or this component/subsystem wants to send
		a command to some \ref IMessageSystemParticipant "message system participant"
		it creates a \ref PackedMessage "packed message" and calls deliverMessage() method. It can specify
		listeners to which this message will be delivered providing \ref IMessageDeliveryPolicy "message delivery policy".
		If no policy is specified, the message will be delivered to all listeners who has subscribed to messages of such type.

		Some user code may want to register message listeners as sniffers.
		Sniffers catch all messages from all senders without considering delivery policy and message type.
		It may be useful for some debug purposes. You can still pass a receive policy to filter out unwanted message types.

		###Notes
		It isn't guaranteed that the message will be delivered instantly. It will be rather delivered "as soon as possible".
		This is due to the possible multithreading. You may want to pass messages between different threads,
		so instead simple callbacks we may want to create a message queue implementation in MessageDispatcher
		and deliver messages in a loop when they come to us.

		 */

		class MessageDispatcher : public Singleton<MessageDispatcher>
		{
			public:
				/**
				 * @brief Default constructor
				 *
				 * Is called by Engine
				 *
				 */
				COMPONENTSYSTEM_EXPORT
				MessageDispatcher ();

				COMPONENTSYSTEM_EXPORT
				virtual ~MessageDispatcher ();

				/**
				 * @brief Registers a new listener
				 * @param message_type_id - %Message type which the listener will wait for
				 * @param listener - %Listener object
				 * @param receive_policy - %Receive policy to filter out received messages
				 */
				COMPONENTSYSTEM_EXPORT
				void addListener ( const MessageType &message_type_id, IMessageListener* listener, IMessageReceivePolicy* receive_policy = nullptr );

				/**
				 * @brief Registers a new listener
				 * @param message_type_name - %String message type representation to wait for
				 * @param listener - %Listener object
				 * @param receive_policy - %Receive policy to filter out received messages
				 */
				COMPONENTSYSTEM_EXPORT
				void addListener ( const std::string &message_type_name, IMessageListener* listener, IMessageReceivePolicy* receive_policy = nullptr );

				/**
				 * @brief Removes listener for a specific message type
				 * @param message_type_id - %Message type id to unsubscribe listener from
				 * @param listener - %Message listener to unsubscribe
				 */
				COMPONENTSYSTEM_EXPORT
				void removeListener ( const MessageType &message_type_id, IMessageListener* listener );

				/**
				 * @brief Removes listener for a specific message type
				 * @param message_type_name - %Message type name to unsubscribe listener from
				 * @param listener - %Message listener to unsubscribe
				 */
				COMPONENTSYSTEM_EXPORT
				void removeListener ( const std::string &message_type_name, IMessageListener* listener );

				/**
				 * @brief Removes listener for all message types
				 * @param listener - Listener object to unsubscribe
				 */
				COMPONENTSYSTEM_EXPORT
				void removeListener ( IMessageListener* listener );

				/**
				 * @brief Registers a listener for **all** message types
				 * @param listener - %Message listener object
				 * @param receive_policy - %Message receive policy to filter out messages
				 */
				COMPONENTSYSTEM_EXPORT
				void addSniffer ( IMessageListener* listener, IMessageReceivePolicy* receive_policy );

				/**
				 * @brief Removes sniffer listener
				 * @param listener - %Listener object to remove
				 */
				COMPONENTSYSTEM_EXPORT
				void removeSniffer ( IMessageListener* listener );

				/**
				 * @brief Changes message listener receive policy
				 * @param message_type_id - %Message type id
				 * @param listener - %Listener object
				 * @param receive_policy - %Message receive policy
				 */
				COMPONENTSYSTEM_EXPORT
				void setListenerReceivePolicy ( const MessageType &message_type_id, IMessageListener* listener, IMessageReceivePolicy* receive_policy );

				/**
				 * @brief Changes message listener receive policy
				 * @param message_type_name - %Message type name
				 * @param listener - %Listener object
				 * @param receive_policy - %Message receive policy
				 */
				COMPONENTSYSTEM_EXPORT
				void setListenerReceivePolicy ( const std::string &message_type_name, IMessageListener* listener, IMessageReceivePolicy* receive_policy );

				/**
				 * @brief Delivers message to all registered listeners
				 * @param msg - %Packed message to deliver
				 * @param delivery_policy - %Delivery policy
				 */
				COMPONENTSYSTEM_EXPORT
				void deliverMessage ( const PackedMessage &msg, IMessageDeliveryPolicy* delivery_policy = nullptr ) const;

			private:

				/// Stored pair <IMessageListener, IMessageReceivePolicy>
				struct RegisteredListener
				{
					RegisteredListener ( IMessageListener* listener, IMessageReceivePolicy* receive_policy )
						: listener ( listener ), receive_policy ( receive_policy ) {}

					IMessageListener* listener; ///< %Message listener
					IMessageReceivePolicy* receive_policy; ///< %Message receive policy
				};

				typedef std::list< RegisteredListener > MessageListenersList;
				typedef std::unordered_map< MessageType, MessageListenersList > MessageListenersMap;

				/// Returns registered listeners for specific message type
				const MessageListenersList* getRegisteredListeners ( const MessageType &message_type_id ) const;

				/// Returns registered listeners for specific message type
				MessageListenersList* getRegisteredListeners ( const MessageType &message_type_id );

				MessageListenersMap listeners; ///< Map of <message type id, listeners list>
				MessageListenersList sniffers; ///< List of sniffers

		};

#ifdef _MSC_VER
#ifndef ComponentSystem_EXPORTS
		extern template class COMPONENTSYSTEM_EXPORT Singleton<MessageDispatcher>;
#else
		template class COMPONENTSYSTEM_EXPORT Singleton<MessageDispatcher>;
#endif
#endif

	} /* namespace Core */
} /* namespace UnknownEngine */
