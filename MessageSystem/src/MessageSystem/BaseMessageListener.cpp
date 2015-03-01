#include <stdafx.h>
#include <MessageSystem/BaseMessageListener.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>
#include <mutex>

namespace UnknownEngine
{
	namespace Core
	{
		BaseMessageListener::BaseMessageListener ( const std::string& object_name) : 
		logger(CREATE_LOGGER(std::string(object_name.c_str()) + ".Listener", Core::LogSeverity::NONE)),
		registered(false),
		name(object_name),
		message_dispatcher(Core::MessageDispatcher::getSingleton())
		{
		}
		
		BaseMessageListener::~BaseMessageListener()
		{
			RELEASE_LOGGER(logger);
		}

		void BaseMessageListener::processMessage ( const PackedMessage& msg )
		{
			Utils::IMessageBuffer *buffer = findMessageBuffer(msg);

			LOG_DEBUG(logger, "Pushing message to buffer: " + MESSAGE_TYPE_NAME(msg.getMessageTypeId()));
			if ( buffer != nullptr ) buffer->push ( msg );
			
			LOG_DEBUG(logger, "Message processed");
		}

		void BaseMessageListener::flushAllMessageBuffers()
		{
			std::lock_guard<LockPrimitive> guard(lock_primitive);
			for ( auto & iter : received_messages )
			{
				LOG_DEBUG(logger, "Flushing message buffers");
				if ( iter.second.message_buffer ) iter.second.message_buffer->flush();
			}
			LOG_DEBUG(logger, "Message buffers flushed");
		}

		void BaseMessageListener::registerAtDispatcher ( )
		{
			for(auto& iter : received_messages)
			{
				LOG_DEBUG(logger, "Registering at message dispatcher");
				if(iter.second.message_buffer) message_dispatcher->addListener(iter.first, this);
			}
			registered = true;
		}

		void BaseMessageListener::unregisterAtDispatcher ( )
		{
			LOG_DEBUG(logger, "Unregistering at message dispatcher");
			message_dispatcher->removeListener(this);
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
				LOG_DEBUG(logger, "Searching for message buffer");
				auto iter = received_messages.find ( msg.getMessageTypeId() );
				if ( iter == received_messages.end() ) throw NoMessageProcessorFoundException ( "Can't find message processor for message type: " + MESSAGE_TYPE_NAME ( msg.getMessageTypeId() ) );
				if ( iter->second.message_buffer ) buffer = iter->second.message_buffer.get();
			}
			return buffer;
		}
		
		BaseMessageListener::ReceivedMessage* BaseMessageListener::createMessageSlot ( const MessageType& message_type )
		{
			LOG_DEBUG(logger, "Creating placeholder for message buffer");
			BaseMessageListener::ReceivedMessage* slot = &received_messages.emplace( message_type, ReceivedMessage() ).first->second;
			LOG_DEBUG(logger, "Message type registered");
			return slot;
		}
		
		const char* BaseMessageListener::getName() const
		{
			return name.c_str();
		}

	}
}
