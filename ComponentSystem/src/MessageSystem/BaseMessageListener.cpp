#include <stdafx.h>
#include <MessageSystem/BaseMessageListener.h>
#include <MessageBuffers/MessageBuffer.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>
#include <EngineContext.h>
#include <LogHelper.h>
#include <mutex>

namespace UnknownEngine
{
	namespace Core
	{
		BaseMessageListener::BaseMessageListener ( const std::string& object_name, EngineContext* engine_context ) : 
		IMessageListener ( object_name ),
		engine_context(engine_context),
		registered(false)
		{
			//log_helper.reset( new Utils::LogHelper(object_name, Utils::LogSeverity::DEBUG, engine_context ) );
		}
		
		BaseMessageListener::~BaseMessageListener()
		{
		}

		void BaseMessageListener::registerSupportedMessageType ( const MessageType& message_type_id, IMessageReceivePolicy* receive_policy )
		{
			LOG_DEBUG(log_helper, "Creating placeholder for message buffer");
			received_messages.emplace ( message_type_id, ReceivedMessage(receive_policy) );
			
			LOG_DEBUG(log_helper, "Message type registered");
		}

		void BaseMessageListener::registerSupportedMessageType ( const std::string& message_type_name, IMessageReceivePolicy* receive_policy )
		{
			registerSupportedMessageType ( MESSAGE_TYPE_ID ( message_type_name ), receive_policy );
		}

		void BaseMessageListener::registerSupportedMessageTypes ( const ReceivedMessageDescriptorsList& received_messages_list )
		{
			for ( const Core::ReceivedMessageDesc & message : received_messages_list )
			{
				if ( message.receive_policy && getMessagingPoliciesManager().isPrefabReceivePolicyType ( message.receive_policy->receive_policy_type_name ) )
				{
					Core::IMessageReceivePolicy* receive_policy = getMessagingPoliciesManager().createPrefabReceiveMessagePolicy (
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
		
		MessagingPoliciesManager& BaseMessageListener::getMessagingPoliciesManager()
		{
			return messaging_policies_manager;
		}

		void BaseMessageListener::processMessage ( const PackedMessage& msg )
		{
			Utils::IMessageBuffer *buffer = findMessageBuffer(msg);

			LOG_DEBUG(log_helper, "Pushing message to buffer: " + MESSAGE_TYPE_NAME(msg.getMessageTypeId()));
			if ( buffer != nullptr ) buffer->push ( msg );
			
			LOG_DEBUG(log_helper, "Message processed");
		}

		void BaseMessageListener::flushAllMessageBuffers()
		{
			std::lock_guard<LockPrimitive> guard(lock_primitive);
			for ( auto & iter : received_messages )
			{
				LOG_DEBUG(log_helper, "Flushing message buffers");
				if ( iter.second.message_buffer ) iter.second.message_buffer->flush();
			}
			LOG_DEBUG(log_helper, "Message buffers flushed");
		}

		void BaseMessageListener::registerAtDispatcher ( )
		{
			for(auto& iter : received_messages)
			{
				LOG_DEBUG(log_helper, "Registering at message dispatcher");
				if(iter.second.message_buffer) engine_context->getMessageDispatcher()->addListener(iter.first, this, iter.second.receive_policy);
			}
			registered = true;
		}

		void BaseMessageListener::unregisterAtDispatcher ( )
		{
			LOG_DEBUG(log_helper, "Unregistering at message dispatcher");
			engine_context->getMessageDispatcher()->removeListener(this);
			registered = false;
		}
		
		bool BaseMessageListener::isRegisteredAtDispatcher()
		{
			return registered;
		}
		
		Utils::IMessageBuffer* BaseMessageListener::findMessageBuffer ( const PackedMessage& msg )
		{
			Utils::IMessageBuffer *buffer = nullptr;
			{
				std::lock_guard<LockPrimitive> guard(lock_primitive);
				LOG_DEBUG(log_helper, "Searching for message buffer");
				auto iter = received_messages.find ( msg.getMessageTypeId() );
				if ( iter == received_messages.end() ) throw NoMessageProcessorFoundException ( "Can't find message processor for message type: " + MESSAGE_TYPE_NAME ( msg.getMessageTypeId() ) );
				if ( iter->second.message_buffer ) buffer = iter->second.message_buffer.get();
			}
			return buffer;
		}
		
	}
}
