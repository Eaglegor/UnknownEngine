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
#include <Properties/Properties.h>
#include <MessageSystem/MessageType.h>
#include "MessageSystemParticipantId.h"
#include "MessagingPoliciesManager.h"
#include <Dictionary.h>
#include <mutex>
#include <vector>

#include <MessageSystem/MessageSenderRules.h>
#include <MessageSystem/MessageListenerRules.h>

namespace UnknownEngine
{
	namespace Core
	{

		class ILogger;
		class IMessageSender;

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
				
				UNKNOWNENGINE_SIMPLE_EXCEPTION(ListenerNotAddedException);
				UNKNOWNENGINE_SIMPLE_EXCEPTION(SenderNotAddedException);
				
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
				
				COMPONENTSYSTEM_EXPORT
				void setListenerRules(const MessageSystemParticipantId &listener_id, const MessageListenerRules &listener_rules);
				
				COMPONENTSYSTEM_EXPORT
				void setSenderRules(const MessageSystemParticipantId &sender_id, const MessageSenderRules &listener_rules);
				
				COMPONENTSYSTEM_EXPORT
				void setSingleListenerRule(const MessageSystemParticipantId& id, const MessageType &message_type, const MessageListenerRule& listener_rule);
				
				COMPONENTSYSTEM_EXPORT
				void setSingleSenderRule(const MessageSystemParticipantId& id, const MessageType &message_type, const MessageSenderRule& sender_rule);
				
				COMPONENTSYSTEM_EXPORT
				void clearListenerRules(const MessageSystemParticipantId &listener_id);
				
				COMPONENTSYSTEM_EXPORT
				void clearSenderRules(const MessageSystemParticipantId &sender_id);
				
				COMPONENTSYSTEM_EXPORT
				void addListener ( const MessageType &message_type, IMessageListener* listener);

				COMPONENTSYSTEM_EXPORT
				void addListener ( const MessageType &message_type, IMessageListener* listener, const MessageListenerRule &listener_rule);
				
				COMPONENTSYSTEM_EXPORT
				void removeListener ( IMessageListener* listener );

				COMPONENTSYSTEM_EXPORT
				void addSender ( const MessageType &message_type, IMessageSender* sender);

				COMPONENTSYSTEM_EXPORT
				void addSender ( const MessageType &message_type, IMessageSender* sender, const MessageSenderRule &sender_rule);
				
				COMPONENTSYSTEM_EXPORT
				void removeSender ( IMessageSender* sender );

			private:

				struct ListenerRules
				{
					std::unordered_map<MessageType, IMessageReceivePolicy*> messages;
				};
				
				struct SenderRules
				{
					std::unordered_map<MessageType, IMessageDeliveryPolicy*> messages;
				};
				
				struct RegisteredListener
				{
					IMessageListener* listener;
					IMessageReceivePolicy* receive_policy;
				};

				struct RegisteredSender
				{
					IMessageSender* sender;
					IMessageDeliveryPolicy* delivery_policy;
				};

				void onNewListener(const MessageType &message_type, IMessageListener* listener, IMessageReceivePolicy* receive_policy);
				void onNewSender(const MessageType &message_type, IMessageSender* sender, IMessageDeliveryPolicy* delivery_policy);
				void onRemoveListener(IMessageListener* listener);
				void onRemoveSender(IMessageSender* sender);

				ListenerRules* getListenerRules(const MessageSystemParticipantId& id);
				SenderRules* getSenderRules(const MessageSystemParticipantId& id);
				
				ListenerRules* createListenerRules(const MessageSystemParticipantId& id);
				SenderRules* createSenderRules(const MessageSystemParticipantId& id);

				typedef std::unordered_map< MessageSystemParticipantId, ListenerRules > ListenerRulesMap;
				typedef std::unordered_map< MessageSystemParticipantId, SenderRules > SenderRulesMap;
				
				typedef std::unordered_map< MessageSystemParticipantId, RegisteredListener > MessageListenersMap;
				typedef std::unordered_map< MessageSystemParticipantId, RegisteredSender > MessageSendersMap;
				
				typedef std::unordered_map<MessageType, MessageListenersMap> MessageTypeListenersMap;
				typedef std::unordered_map<MessageType, MessageSendersMap> MessageTypeSendersMap;
				
				MessageTypeListenersMap listeners;
				MessageTypeSendersMap senders;
				
				ListenerRulesMap listener_rules;
				SenderRulesMap sender_rules;
				
				typedef std::mutex LockPrimitive;
				LockPrimitive lock;
				
				ILogger* logger;
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
