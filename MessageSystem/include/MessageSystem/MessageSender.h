#pragma once

#include <unordered_map>

#include <MessageSystem/Policies/Sender/IMessageDeliveryPolicy.h>
#include <MessageSystem/Policies/Listener/IMessageReceivePolicy.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageDictionary.h>
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
		public:
			
			MessageSender(const std::string &sender_name):
			message_type( MESSAGE_TYPE_ID(MessageClass::getTypeName()) ),
			name(sender_name),
			message_dispatcher(MessageDispatcher::getSingleton()),
			is_registered(false)
			{}
			
			~MessageSender()
			{
				if(is_registered)
				{
					unregisterAtDispatcher();
				}
			}
			
			virtual const char* getName()
			{
				return name.c_str();
			}
			
			virtual void sendMessage(const MessageClass& message)
			{
				if(!is_registered) registerAtDispatcher();
				PackedMessage msg(message, message_type);
				
				for(auto &message_listener: listeners)
				{
					message_listener.second->processMessage(msg);
				}
			}

			virtual void attachListener ( IMessageListener* listener) override
			{
				auto iter = listeners.find(listener->getName());
				if(iter == listeners.end())
				{
					listeners.emplace(listener->getName(), listener);
				}
			}
			
			virtual void detachListener ( IMessageListener* listener ) override
			{
				auto iter = listeners.find(listener->getName());
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
			MessageType message_type;
			const std::string name;
			Core::MessageDispatcher* message_dispatcher;
			
			void registerAtDispatcher()
			{
				message_dispatcher->addSender(message_type, this);
				is_registered = true;
			}
			
			void unregisterAtDispatcher()
			{
				message_dispatcher->removeSender(this);
				is_registered = false;
			}

			bool is_registered;
			std::unordered_map<std::string, IMessageListener*> listeners;
		};
		
	}
}