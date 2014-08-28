#include <MessageSystem/BaseMessageListener.h>
#include <MessageBuffers/MessageBuffer.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>
#include <EngineContext.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Core
	{
		BaseMessageListener::BaseMessageListener ( const std::string& object_name, EngineContext* engine_context ) : 
		IMessageListener ( object_name ),
		messaging_policies_manager(engine_context),
		engine_context(engine_context)
		{
			//log_helper.reset( new LogHelper(object_name, LogMessage::Severity::LOG_SEVERITY_DEBUG, engine_context ) );
		}

		bool BaseMessageListener::registerMessageBuffer ( const Core::MessageType& message_type, std::unique_ptr< Utils::IMessageBuffer > buffer )
		{
			LOG_DEBUG(log_helper, "Register buffer: Acquiring lock...");
			
			std::lock_guard<std::mutex> guard( message_buffers_mutex );
			
			LOG_DEBUG(log_helper, "Searching for supported message type...");
			
			auto iter = received_messages.find ( message_type );
			if ( iter == received_messages.end() ) return false;
			
			LOG_DEBUG(log_helper, "Message buffer found, ...");
			
			iter->second.message_buffer = std::move(buffer);
			
			LOG_DEBUG(log_helper, "Buffer registered...");
			
			return true;
		}

		void BaseMessageListener::registerSupportedMessageType ( const UnknownEngine::Core::MessageType& message_type_id, UnknownEngine::Core::IMessageReceivePolicy* receive_policy )
		{
			LOG_DEBUG(log_helper, "Register message type: Acquiring lock...");
			std::lock_guard<std::mutex> guard( message_buffers_mutex );
			
			LOG_DEBUG(log_helper, "Creating placeholder for message buffer");
			received_messages.emplace ( message_type_id, ReceivedMessage(receive_policy) );
			
			LOG_DEBUG(log_helper, "Message type registered");
		}

		void BaseMessageListener::registerSupportedMessageType ( const std::string& message_type_name, UnknownEngine::Core::IMessageReceivePolicy* receive_policy )
		{
			registerSupportedMessageType ( MESSAGE_TYPE_ID ( message_type_name ), receive_policy );
		}

		MessagingPoliciesManager& BaseMessageListener::getMessagingPoliciesManager()
		{
			return messaging_policies_manager;
		}

		void BaseMessageListener::processMessage ( const PackedMessage& msg )
		{
			LOG_DEBUG(log_helper, "Process message: Acquiring lock");
			std::lock_guard<std::mutex> guard( message_buffers_mutex );
			
			LOG_DEBUG(log_helper, "Searching for message buffer");
			auto iter = received_messages.find ( msg.getMessageTypeId() );
			if ( iter == received_messages.end() ) throw NoMessageProcessorFoundException ( "Can't find message processor for message type: " + MESSAGE_TYPE_NAME ( msg.getMessageTypeId() ) );
			
			LOG_DEBUG(log_helper, "Pushing message to buffer");
			if ( iter->second.message_buffer ) iter->second.message_buffer->push ( msg );
		}

		void BaseMessageListener::flushAllMessageBuffers()
		{
			LOG_DEBUG(log_helper, "Flush all buffers: Acquiring lock");
			std::lock_guard<std::mutex> guard( message_buffers_mutex );
			for ( auto & iter : received_messages )
			{
				LOG_DEBUG(log_helper, "Flushing message buffers");
				if ( iter.second.message_buffer ) iter.second.message_buffer->flush();
			}
			LOG_DEBUG(log_helper, "Message buffers flushed");
		}

		void BaseMessageListener::registerAtDispatcher ( )
		{
			LOG_DEBUG(log_helper, "Registering at dispatcher: Acquiring lock");
			std::lock_guard<std::mutex> guard( message_buffers_mutex );
			for(auto& iter : received_messages)
			{
				LOG_DEBUG(log_helper, "Registering at message dispatcher");
				if(iter.second.message_buffer) engine_context->getMessageDispatcher()->addListener(iter.first, this, iter.second.receive_policy);
			}
		}

		void BaseMessageListener::unregisterAtDispatcher ( )
		{
			LOG_DEBUG(log_helper, "Unregistering at message dispatcher");
			engine_context->getMessageDispatcher()->removeListener(this);
		}
		
	}
}
