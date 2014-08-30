#pragma once

#include <MessageSystem/Policies/IMessageDeliveryPolicy.h>
#include <MessageSystem/MessageDispatcher.h>
#include <EngineContext.h>

namespace UnknownEngine
{
	namespace Core
	{
		
		class MessageSystemParticipantId;
		
		template<typename MessageClass>
		class MessageSender
		{
		public:
			MessageSender(const MessageSystemParticipantId &message_system_participant_id, EngineContext* engine_context, IMessageDeliveryPolicy* message_delivery_policy = nullptr):
			engine_context(engine_context),
			message_delivery_policy(message_delivery_policy),
			message_packer(message_system_participant_id)
			{}
			
			void sendMessage(const MessageClass& message)
			{
				engine_context->getMessageDispatcher()->deliverMessage(message_packer.packMessage(message), message_delivery_policy);
			}
			
		private:
			IMessageDeliveryPolicy* message_delivery_policy;
			EngineContext* engine_context;
			typename MessageClass::PackerClass message_packer;
		};
		
	}
}