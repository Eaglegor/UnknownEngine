#include <MessageSystem/BaseMessageListener.h>
#include <MessageBuffers/MessageBuffer.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine
{
	namespace Core
	{
		BaseMessageListener::BaseMessageListener ( const std::string& object_name ) : 
		IMessageListener ( object_name )
		{}

		bool BaseMessageListener::registerMessageBuffer ( const Core::MessageType& message_type, std::unique_ptr< Utils::IMessageBuffer > buffer )
		{
			std::lock_guard<std::mutex> ( message_buffers_mutex );
			auto& iter = received_messages.find ( message_type );
			if ( iter == received_messages.end() ) return false;
			iter.second->message_buffer = buffer;

			return true;
		}

		void BaseMessageListener::registerSupportedMessageType ( const UnknownEngine::Core::MessageType& message_type_id, UnknownEngine::Core::IMessageReceivePolicy* receive_policy )
		{
			std::lock_guard<std::mutex> ( message_buffers_mutex );
			received_messages.emplace ( message_type_id, ReceivedMessage(receive_policy) );
		}

		void BaseMessageListener::registerSupportedMessageType ( const std::string& message_type_name, UnknownEngine::Core::IMessageReceivePolicy* receive_policy )
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
			auto& iter = received_messages.find ( msg.getMessageTypeId() );
			if ( iter == received_messages.end() ) throw NoMessageProcessorFoundException ( "Can't find message processor for message type: " + MESSAGE_TYPE_NAME ( msg.getMessageTypeId() ) );
			if ( iter.second->message_buffer ) iter.second->message_buffer->push ( msg );
		}

		void BaseMessageListener::flushAllMessageBuffers()
		{
			std::lock_guard<std::mutex> ( message_buffers_mutex );
			for ( auto & iter : received_messages )
			{
				if ( iter.second->message_buffer ) iter.second->message_buffer->flush();
			}
		}

		void BaseMessageListener::registerListener ( MessageDispatcher* message_dispatcher )
		{
			std::lock_guard<std::mutex> ( message_buffers_mutex );
			for(auto& iter : received_messages)
			{
				if(iter.second->message_buffer) message_dispatcher->addListener(iter.first, this, iter.second->receive_policy);
			}
		}

		void BaseMessageListener::unregisterListener ( MessageDispatcher* message_dispatcher )
		{
			message_dispatcher->removeListener(this);
		}

		void BaseMessageListener::setSupportedMessageTypes ( const ReceivedMessageDescriptorsList& received_messages_list )
		{
			for ( const Core::ReceivedMessageDesc & message : received_messages_list )
			{
				if( message.receive_policy && messaging_policies_manager.isPrefabReceivePolicyType(message.receive_policy->receive_policy_type_name))
				{
					Core::IMessageReceivePolicy* receive_policy = messaging_policies_manager.createPrefabDeliveryMessagePolicy(
						message.receive_policy->receive_policy_type_name,
						message.receive_policy->receive_policy_options
					);
					
					registerSupportedMessageType ( message.message_type_name, receive_policy );
				}
				else
				{
					registerSupportedMessageType ( message.message_type_name, nullptr );
				}
			}
		}
		
	}
}
