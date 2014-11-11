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
			~BaseMessageListener ();
			
			COMPONENTSYSTEM_EXPORT
			void registerSupportedMessageType( const std::string& message_type_name, IMessageReceivePolicy* receive_policy);

			COMPONENTSYSTEM_EXPORT
			void registerSupportedMessageType( const MessageType& message_type_id, IMessageReceivePolicy* receive_policy);

			template<typename MessageClass, typename BufferClass, typename... Args>
			bool createMessageBuffer(const Args&&... buffer_constructor_parameters)
			{
				static_assert(std::is_base_of<Utils::IMessageBuffer, BufferClass>::value, "Message buffer must implement Utils::IMessageBuffer");
				static_assert(std::is_base_of<Core::Message, MessageClass>::value, "Message class must inherit from Core::Message");
				
				auto iter = received_messages.find(MESSAGE_TYPE_ID(MessageClass::getTypeName()));
				if (iter == received_messages.end()) {
					LOG_DEBUG(log_helper, "Message slot not found at listener: " + getName() + " Message type: " + std::string(MessageClass::getTypeName()) +
						". Listener is not listening to this message type.");
					return false;
				}

				LOG_DEBUG(log_helper, "Found message slot - creating buffer");

				iter->second.message_buffer.reset(new BufferClass(std::forward<Args...>(buffer_constructor_parameters)));

				LOG_DEBUG(log_helper, "Message buffer created");

				return true;
			}

			template<typename CallbackOwnerClass, typename MessageClass, typename BufferClass, typename... Args>
			bool createMessageBuffer(CallbackOwnerClass* callback_owner_class, void (CallbackOwnerClass::*callback_method)(const MessageClass&))
			{

				typedef std::function<void(const MessageClass&)> MessageProcessor;
				MessageProcessor callback = std::bind(callback_method, callback_owner_class, std::placeholders::_1);

				return createMessageBuffer<MessageClass, BufferClass>(callback);
			}

			
			template<typename BufferClass>
			bool registerMessageBuffer( const BufferClass &buffer)
			{
				static_assert(std::is_base_of<Utils::IMessageBuffer, BufferClass>::value, "Message buffer must implement Utils::IMessageBuffer" );

				LOG_DEBUG(log_helper, "Searching for supported message type...");

				auto iter = received_messages.find ( buffer.getMessageType() );
				if ( iter == received_messages.end() ) return false;

				LOG_DEBUG(log_helper, "Message buffer found, ...");

				iter->second.message_buffer.reset(new BufferClass( buffer ) );

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

			typedef std::recursive_mutex LockPrimitive;
			
			struct ReceivedMessage
			{
				std::unique_ptr<Utils::IMessageBuffer> message_buffer;
				IMessageReceivePolicy* receive_policy;
				
				ReceivedMessage(IMessageReceivePolicy* receive_policy):
				receive_policy(receive_policy)
				{}
				
				ReceivedMessage(const ReceivedMessage &msg):
				receive_policy(msg.receive_policy){};

			};

			Utils::IMessageBuffer *findMessageBuffer(const PackedMessage &msg);
			
			std::unordered_map<MessageType, ReceivedMessage > received_messages;
			MessagingPoliciesManager messaging_policies_manager;
			EngineContext* engine_context;
			
			std::unique_ptr<Utils::LogHelper> log_helper;
			
			LockPrimitive lock_primitive;
		};

	}

}