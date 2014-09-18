#pragma once

#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <EngineContext.h>
#include <MessageSystem/PackedMessage.h>

namespace UnknownEngine
{
	namespace Core
	{
		
		struct MessageSystemParticipantId;
		
		template<typename MessageClass>
		class MessageSender
		{
		public:
			MessageSender(const MessageSystemParticipantId &sender_info, EngineContext* engine_context, IMessageDeliveryPolicy* message_delivery_policy = nullptr):
			engine_context(engine_context),
			message_delivery_policy(message_delivery_policy),
			sender_info(sender_info),
			message_type( MESSAGE_TYPE_ID(MessageClass::getTypeName()) )
			{}
			
			void sendMessage(const MessageClass& message)
			{
				engine_context->getMessageDispatcher()->deliverMessage( PackedMessage(message, message_type, sender_info), message_delivery_policy);
			}
			
		private:
			EngineContext* engine_context;
			IMessageDeliveryPolicy* message_delivery_policy;
			MessageSystemParticipantId sender_info;
			MessageType message_type;
		};
		
	}
}