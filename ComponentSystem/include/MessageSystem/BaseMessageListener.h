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
#include <ComponentSystem_export.h>

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
			
			COMPONENTSYSTEM_EXPORT
			BaseMessageListener ( const std::string& object_name, EngineContext* engine_context );
			
			COMPONENTSYSTEM_EXPORT
			void registerSupportedMessageType( const std::string& message_type_name, IMessageReceivePolicy* receive_policy);

			COMPONENTSYSTEM_EXPORT
			void registerSupportedMessageType( const MessageType& message_type_id, IMessageReceivePolicy* receive_policy);

			template<typename BufferClass>
			bool registerMessageBuffer( const MessageType& message_type, const BufferClass &buffer)
			{
				static_assert(std::is_base_of<Utils::IMessageBuffer, BufferClass>::value, "Trying to register not a message buffer class as message buffer" );

				LOG_DEBUG(log_helper, "Register buffer: Acquiring lock...");

				std::lock_guard<std::mutex> guard( message_buffers_mutex );

				LOG_DEBUG(log_helper, "Searching for supported message type...");

				auto iter = received_messages.find ( message_type );
				if ( iter == received_messages.end() ) return false;

				LOG_DEBUG(log_helper, "Message buffer found, ...");

				iter->second.setMessageBuffer( buffer );

				LOG_DEBUG(log_helper, "Buffer registered...");

				return true;
			}

			COMPONENTSYSTEM_EXPORT
			MessagingPoliciesManager& getMessagingPoliciesManager();
			
			COMPONENTSYSTEM_EXPORT
			virtual void processMessage ( const PackedMessage& msg );

			COMPONENTSYSTEM_EXPORT
			virtual void flushAllMessageBuffers();

			COMPONENTSYSTEM_EXPORT
			void registerAtDispatcher();

			COMPONENTSYSTEM_EXPORT
			void unregisterAtDispatcher();
			
		private:

			struct ReceivedMessage
			{
				std::unique_ptr<Utils::IMessageBuffer> message_buffer;
				IMessageReceivePolicy* receive_policy;
				
				ReceivedMessage(IMessageReceivePolicy* receive_policy):
				receive_policy(receive_policy)
				{}
				
				ReceivedMessage(const ReceivedMessage &msg):
				receive_policy(msg.receive_policy){};

				template<typename T>
				void setMessageBuffer(const T& new_message_buffer)
				{
					message_buffer.reset(new T(new_message_buffer));
				}

			};
			
			std::unordered_map<MessageType, ReceivedMessage > received_messages;
			MessagingPoliciesManager messaging_policies_manager;
			EngineContext* engine_context;
			
			std::unique_ptr<LogHelper> log_helper;
			
			std::mutex message_buffers_mutex;
		};

	}

}