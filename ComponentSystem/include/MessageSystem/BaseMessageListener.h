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
#include <LogHelper.h>

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

			void registerAtDispatcher();
			void unregisterAtDispatcher();
			
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
			EngineContext* engine_context;
			
			std::unique_ptr<LogHelper> log_helper;
			
			std::mutex message_buffers_mutex;
		};

	}
}