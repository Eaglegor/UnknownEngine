#pragma once

#include <unordered_map>

#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <MessageSystem/Policies/IMessageReceivePolicy.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/IMessageSystemParticipant.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <EngineContext.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/IMessageSender.h>

namespace UnknownEngine
{
	namespace Core
	{
		template<typename MessageClass>
		class MessageSender : public IMessageSender
		{
		private:
			struct RegisteredListener
			{
				IMessageListener* listener;
				
				bool operator==(const RegisteredListener& rhs) const
				{
					return listener->getMessageSystemParticipantId() == rhs.listener->getMessageSystemParticipantId();
				}
			};
			
		public:
			
			MessageSender(const std::string &sender_name, EngineContext* engine_context, IMessageDeliveryPolicy* message_delivery_policy = nullptr):
			IMessageSender(sender_name),
			engine_context(engine_context),
			message_delivery_policy(message_delivery_policy),
			message_type( MESSAGE_TYPE_ID(MessageClass::getTypeName()) ),
			is_registered(false)
			{}
			
			~MessageSender()
			{
				if(is_registered)
				{
					unregisterAtDispatcher();
				}
			}
			
			virtual void sendMessage(const MessageClass& message)
			{
				if(!is_registered) registerAtDispatcher();
				PackedMessage msg(message, message_type);
				
				for(auto &message_listener: listeners)
				{
					message_listener.second.listener->processMessage(msg);
				}
			}

			virtual void attachListener ( IMessageListener* listener, IMessageReceivePolicy* receive_policy ) override
			{
				RegisteredListener registered_listener;
				registered_listener.listener = listener;
				listeners.emplace(listener->getMessageSystemParticipantId(), registered_listener);
			}
			
			virtual void detachListener ( IMessageListener* listener ) override
			{
				auto iter = listeners.find(listener->getMessageSystemParticipantId());
				if(iter != listeners.end())
				{
					listeners.erase(iter);
				}
			}
			
			virtual void detachAllListeners()
			{
				listeners.clear();
			};
			
		private:
			EngineContext* engine_context;
			IMessageDeliveryPolicy* message_delivery_policy;
			MessageType message_type;
			
			void registerAtDispatcher()
			{
				engine_context->getMessageDispatcher()->addSender(message_type, this);
				is_registered = true;
			}
			
			void unregisterAtDispatcher()
			{
				engine_context->getMessageDispatcher()->removeSender(this);
			}

			bool is_registered;
			std::unordered_map<MessageSystemParticipantId, RegisteredListener> listeners;
		};
		
	}
}