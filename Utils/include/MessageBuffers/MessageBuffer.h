#pragma once

#include <InlineSpecification.h>
#include <MessageSystem/PackedMessage.h>
#include <MessageSystem/MessageDictionary.h>
#include <functional>

namespace UnknownEngine
{
	namespace Utils
	{
		
		class IMessageBuffer
		{
		public:
			IMessageBuffer& operator<<(const Core::PackedMessage& message)
			{
				push(message);
				return *this;
			}

			virtual ~IMessageBuffer(){}
			
			virtual Core::MessageType getMessageType() const = 0;
			virtual void push(const Core::PackedMessage& message) = 0;
			virtual void flush() = 0;
		};
		
		template <typename MessageClass>
		class MessageBuffer : public IMessageBuffer
		{
		public:
			
			MessageBuffer( std::function<void(const MessageClass&)> process_message_callback ):
			process_message_callback(process_message_callback),
			message_type( MESSAGE_TYPE_ID(MessageClass::getTypeName()) )
			{}
			
			void push(const Core::PackedMessage& message) override
			{
				pushConcreteMessage(message.get<MessageClass>());
			}
			
			virtual Core::MessageType getMessageType() const override
			{
				return message_type;
			}

		protected:
			virtual void pushConcreteMessage(const MessageClass& message) = 0;
			
			std::function< void(const MessageClass&)> process_message_callback;

		private:
			Core::MessageType message_type;
		};
		
	}
}