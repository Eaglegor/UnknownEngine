#pragma once

#include <MessageSystem_export.h>
#include <unordered_map>
#include <list>

#include <Singleton.h>
#include <NumericIdentifierType.h>
#include <Properties/Properties.h>
#include <MessageSystem/MessageType.h>
#include <MessageSystem/Policies/MessagingPoliciesManager.h>
#include <Dictionary.h>
#include <mutex>
#include <vector>

#include <MessageSystem/Policies/Sender/MessageSenderRules.h>
#include <MessageSystem/Policies/Listener/MessageListenerRules.h>

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
				MessageDispatcher ();
				virtual ~MessageDispatcher ();
				
				MESSAGESYSTEM_EXPORT
				void setListenerRules(const char* listener_name, const MessageListenerRules &listener_rules);
				
				MESSAGESYSTEM_EXPORT
				void setSenderRules(const char* sender_name, const MessageSenderRules &listener_rules);
				
				MESSAGESYSTEM_EXPORT
				void clearListenerRules(const char* listener_name);
				
				MESSAGESYSTEM_EXPORT
				void clearSenderRules(const char* sender_name);
				
				MESSAGESYSTEM_EXPORT
				void addListener ( const MessageType &message_type, IMessageListener* listener);
				
				MESSAGESYSTEM_EXPORT
				void removeListener ( IMessageListener* listener );

				MESSAGESYSTEM_EXPORT
				void addSender ( const MessageType &message_type, IMessageSender* sender);

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

				ListenerRules* getListenerRules(const std::string &listener_name);
				SenderRules* getSenderRules(const std::string &sender_name);
				
				ListenerRules* createListenerRules(const std::string &listener_name);
				SenderRules* createSenderRules(const std::string &sender_name);

				typedef std::unordered_map< std::string, ListenerRules > ListenerRulesMap;
				typedef std::unordered_map< std::string, SenderRules > SenderRulesMap;
				
				typedef std::unordered_map< std::string, RegisteredListener > MessageListenersMap;
				typedef std::unordered_map< std::string, RegisteredSender > MessageSendersMap;
				
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
