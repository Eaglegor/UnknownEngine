#pragma once

#include <boost/optional.hpp>
#include <mutex>
#include <unordered_map>

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/MessageType.h>
#include <MessageSystem/MessagingPoliciesManager.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <MessageBuffers/MessageBuffer.h>
#include <Exception.h>


namespace UnknownEngine
{
	namespace Utils
	{
		class IMessageBuffer;
	}
	
	namespace Core
	{
		
		class MessageDispatcher;
		
		class BaseMessageListener : public IMessageListener
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(NoMessageProcessorFoundException);
			
			BaseMessageListener ( const std::string& object_name, EngineContext* engine_context );
			
			void registerSupportedMessageType( const std::string& message_type_name, IMessageReceivePolicy* receive_policy);
			void registerSupportedMessageType( const MessageType& message_type_id, IMessageReceivePolicy* receive_policy);
			
			bool registerMessageBuffer( const MessageType& message_type, std::unique_ptr<Utils::IMessageBuffer> buffer);

			MessagingPoliciesManager& getMessagingPoliciesManager();
			
			virtual void processMessage ( const PackedMessage& msg );
			virtual void flushAllMessageBuffers();
			
			virtual void registerListener(MessageDispatcher* message_dispatcher);
			virtual void unregisterListener(MessageDispatcher* message_dispatcher);
			
			virtual void setSupportedMessageTypes(const ReceivedMessageDescriptorsList& received_messages_list);
			
		private:
			
			struct ReceivedMessage
			{
				std::unique_ptr<Utils::IMessageBuffer> message_buffer;
				IMessageReceivePolicy* receive_policy;
				
				ReceivedMessage(IMessageReceivePolicy* receive_policy):
				receive_policy(receive_policy)
				{}
				
			};
			
			std::unordered_map<MessageType, ReceivedMessage > received_messages;
			MessagingPoliciesManager messaging_policies_manager;
			
			std::mutex message_buffers_mutex;
		};
		
	}
}