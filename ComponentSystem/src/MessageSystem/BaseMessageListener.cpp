#include <MessageSystem/BaseMessageListener.h>
#include <MessageBuffers/MessageBuffer.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine
{
	namespace Core
	{
		BaseMessageListener::BaseMessageListener ( const std::string& object_name ) : IMessageListener ( object_name )
		{}

		bool BaseMessageListener::registerMessageBuffer ( const Core::MessageType& message_type, std::unique_ptr< Utils::IMessageBuffer > buffer )
		{
			std::lock_guard<std::mutex> ( message_buffers_mutex );
			auto& iter = message_buffers.find ( message_type );
			if ( iter == message_buffers.end() ) return false;
			iter.second = buffer;

			return true;
		}

		void BaseMessageListener::registerSupportedMessageType ( const MessageType& message_type_id )
		{
			std::lock_guard<std::mutex> ( message_buffers_mutex );
			message_buffers.emplace ( message_type_id, nullptr );
		}

		void BaseMessageListener::registerSupportedMessageType ( const std::string& message_type_name )
		{
			registerSupportedMessageType ( MESSAGE_TYPE_ID ( message_type_name ) );
		}

		MessagingPoliciesManager& BaseMessageListener::getMessagingPoliciesManager()
		{
			return messaging_policies_manager;
		}

		void BaseMessageListener::processMessage ( const PackedMessage& msg )
		{
			std::lock_guard<std::mutex> ( message_buffers_mutex );
			auto& iter = message_buffers.find ( msg.getMessageTypeId() );
			if ( iter == message_buffers.end() ) throw NoMessageProcessorFoundException ( "Can't find message processor for message type: " + MESSAGE_TYPE_NAME ( msg.getMessageTypeId() ) );
			if ( *iter.second ) iter.second->push ( msg );
		}

		void BaseMessageListener::flushAllMessageBuffers()
		{
			std::lock_guard<std::mutex> ( message_buffers_mutex );
			for ( auto & iter : message_buffers )
			{
				if ( *iter.second ) iter.second->flush();
			}
		}

	}
}
