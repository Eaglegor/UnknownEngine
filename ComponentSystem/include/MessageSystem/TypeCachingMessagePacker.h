#pragma once
#include <MessageSystem/MessagePacker.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{
		template<typename MessageClass>
		class TypeCachingMessagePacker : public MessagePacker<MessageClass>
		{
		public:
			TypeCachingMessagePacker(const MessageSystemParticipantId& sender_info):
			MessagePacker<MessageClass>(sender_info),
			message_type(INVALID_NUMERIC_IDENTIFIER)
			{
			}
			
			const MessageType& getMessageType(){
				if(message_type == INVALID_NUMERIC_IDENTIFIER) message_type = MESSAGE_TYPE_ID(MessageClass::getTypeName());
				return message_type;
			}
			
		private:
			MessageType message_type;
		};
	}
}