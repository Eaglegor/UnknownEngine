#pragma once

#include <InlineSpecification.h>
#include <MessageSystem/PackedMessage.h>
#include <functional>

namespace UnknownEngine
{
	namespace Utils
	{
		
		class IMessageBuffer
		{
		public:
			void operator<<(const Core::PackedMessage& message)
			{
				push(message);
			}

			virtual ~IMessageBuffer(){}
			
			virtual void push(const Core::PackedMessage& message) = 0;
			virtual void flush() = 0;
		};
		
		template <typename MessageClass>
		class MessageBuffer : public IMessageBuffer
		{
		public:
			MessageBuffer( std::function<void(const MessageClass&)> process_message_callback ):
			process_message_callback(process_message_callback){}
			
			void push(const Core::PackedMessage& message)
			{
				pushConcreteMessage(message.get<MessageClass>());
			}
			
		protected:
			virtual void pushConcreteMessage(const MessageClass& message) = 0;
			
			std::function< void(const MessageClass&)> process_message_callback;
		};
		
	}
}