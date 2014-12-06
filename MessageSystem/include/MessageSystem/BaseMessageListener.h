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
#include <Logging.h>
#include <MessageSystem/Message.h>
#include <MessageSystem_export.h>

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
			
			MESSAGESYSTEM_EXPORT
			BaseMessageListener ( const std::string& object_name, EngineContext* engine_context );
			
			MESSAGESYSTEM_EXPORT
			~BaseMessageListener ();
			
			MESSAGESYSTEM_EXPORT
			void registerSupportedMessageType( const std::string& message_type_name);

			MESSAGESYSTEM_EXPORT
			void registerSupportedMessageType( const MessageType& message_type_id);
			
			MESSAGESYSTEM_EXPORT
			void registerSupportedMessageTypes(const ReceivedMessageDescriptorsList& received_messages_list);

			template<typename MessageClass, typename BufferClass, typename... Args>
			bool createMessageBuffer(Args&&... buffer_constructor_parameters)
			{
				static_assert(std::is_base_of<Utils::IMessageBuffer, BufferClass>::value, "Message buffer must implement Utils::IMessageBuffer");
				static_assert(std::is_base_of<Core::Message, MessageClass>::value, "Message class must inherit from Core::Message");
				
				ReceivedMessage* iter = createMessageSlot(MESSAGE_TYPE_ID(MessageClass::getTypeName()));

				LOG_DEBUG(logger, "Found message slot - creating buffer");

				iter->message_buffer.reset(new BufferClass(std::forward<Args>(buffer_constructor_parameters)...));

				LOG_DEBUG(logger, "Message buffer created");

				return true;
			}
			
			MESSAGESYSTEM_EXPORT
			virtual void processMessage ( const PackedMessage& msg ) override;

			MESSAGESYSTEM_EXPORT
			virtual void flushAllMessageBuffers();

			MESSAGESYSTEM_EXPORT
			void registerAtDispatcher();

			MESSAGESYSTEM_EXPORT
			void unregisterAtDispatcher();
			
			MESSAGESYSTEM_EXPORT
			bool isRegisteredAtDispatcher();
			
		private:
			typedef std::recursive_mutex LockPrimitive;
			
			struct ReceivedMessage
			{
				std::unique_ptr<Utils::IMessageBuffer> message_buffer;
				
				ReceivedMessage(){}
				ReceivedMessage(const ReceivedMessage& msg){}
			};

			MESSAGESYSTEM_EXPORT
			ReceivedMessage *createMessageSlot(const MessageType &message_type);
			Utils::IMessageBuffer *findMessageBuffer(const PackedMessage &msg);
			
			std::unordered_map<MessageType, ReceivedMessage > received_messages;
			EngineContext* engine_context;
			
			ILogger* logger;
			
			LockPrimitive lock_primitive;
			
			bool registered;
		};

	}

}