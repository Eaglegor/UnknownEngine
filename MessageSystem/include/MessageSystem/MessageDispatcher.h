#pragma once

#include <MessageSystem_export.h>
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

		class MessageDispatcher : public Singleton<MessageDispatcher>
		{
			public:
				
				UNKNOWNENGINE_SIMPLE_EXCEPTION(ListenerNotAddedException);
				UNKNOWNENGINE_SIMPLE_EXCEPTION(SenderNotAddedException);

				MessageDispatcher ();
				virtual ~MessageDispatcher ();
				
				MESSAGESYSTEM_EXPORT
				void setListenerRules(const MessageSystemParticipantId &listener_id, const MessageListenerRules &listener_rules);
				
				MESSAGESYSTEM_EXPORT
				void setSenderRules(const MessageSystemParticipantId &sender_id, const MessageSenderRules &listener_rules);
				
				MESSAGESYSTEM_EXPORT
				void setSingleListenerRule(const MessageSystemParticipantId& id, const MessageType &message_type, const MessageListenerRule& listener_rule);
				
				MESSAGESYSTEM_EXPORT
				void setSingleSenderRule(const MessageSystemParticipantId& id, const MessageType &message_type, const MessageSenderRule& sender_rule);
				
				MESSAGESYSTEM_EXPORT
				void clearListenerRules(const MessageSystemParticipantId &listener_id);
				
				MESSAGESYSTEM_EXPORT
				void clearSenderRules(const MessageSystemParticipantId &sender_id);
				
				MESSAGESYSTEM_EXPORT
				void addListener ( const MessageType &message_type, IMessageListener* listener);

				MESSAGESYSTEM_EXPORT
				void addListener ( const MessageType &message_type, IMessageListener* listener, const MessageListenerRule &listener_rule);
				
				MESSAGESYSTEM_EXPORT
				void removeListener ( IMessageListener* listener );

				MESSAGESYSTEM_EXPORT
				void addSender ( const MessageType &message_type, IMessageSender* sender);

				MESSAGESYSTEM_EXPORT
				void addSender ( const MessageType &message_type, IMessageSender* sender, const MessageSenderRule &sender_rule);
				
				MESSAGESYSTEM_EXPORT
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
#ifndef MessageSystem_EXPORTS
		extern template class MESSAGESYSTEM_EXPORT Singleton<MessageDispatcher>;
#else
		template class MESSAGESYSTEM_EXPORT Singleton<MessageDispatcher>;
#endif
#endif

	} /* namespace Core */
} /* namespace UnknownEngine */
