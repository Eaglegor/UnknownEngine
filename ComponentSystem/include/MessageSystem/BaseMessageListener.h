#pragma once

#include <boost/optional.hpp>
#include <mutex>
#include <unordered_map>

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/MessageType.h>
#include <MessageSystem/MessagingPoliciesManager.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <Exception.h>


namespace UnknownEngine
{
	namespace Utils
	{
		class IMessageBuffer;
	}
	
	namespace Core
	{
		
		class BaseMessageListener : public IMessageListener
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(NoMessageProcessorFoundException);
			
			BaseMessageListener ( const std::string& object_name );
			
			void registerSupportedMessageType(const std::string &message_type_name);
			void registerSupportedMessageType(const MessageType &message_type_id);
			
			bool registerMessageBuffer( const MessageType& message_type, std::unique_ptr<Utils::IMessageBuffer> buffer);

			MessagingPoliciesManager& getMessagingPoliciesManager();
			
			virtual void processMessage ( const PackedMessage& msg );
			
		private:
			std::unordered_map<MessageType, std::unique_ptr<Utils::IMessageBuffer> > message_buffers;
			MessagingPoliciesManager messaging_policies_manager;
			std::mutex message_buffers_mutex;
			
		};
		
	}
}