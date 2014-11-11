#pragma once

#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/IMessageSystemParticipant.h>
#include <MessageSystem/MessageSystemParticipantId.h>
#include <EngineContext.h>
#include <MessageSystem/PackedMessage.h>

namespace UnknownEngine
{
	namespace Core
	{
		
		struct MessageSystemParticipantId;
		
		template<typename MessageClass>
		class MessageSender : public IMessageSystemParticipant
		{
		public:
			
			MessageSender(const std::string &sender_name, EngineContext* engine_context, IMessageDeliveryPolicy* message_delivery_policy = nullptr):
			IMessageSystemParticipant(sender_name),
			engine_context(engine_context),
			message_delivery_policy(message_delivery_policy),
			message_type( MESSAGE_TYPE_ID(MessageClass::getTypeName()) )
			{}
			
			void sendMessage(const MessageClass& message)
			{
				engine_context->getMessageDispatcher()->deliverMessage( PackedMessage(message, message_type, getMessageSystemParticipantId()), message_delivery_policy);
			}
			
		private:
			EngineContext* engine_context;
			IMessageDeliveryPolicy* message_delivery_policy;
			MessageType message_type;
		};
		
	}
}