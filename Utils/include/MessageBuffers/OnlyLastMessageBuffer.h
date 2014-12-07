#pragma once

#include <mutex>
#include <memory>
#include <MessageBuffers/MessageBuffer.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template <typename MessageClass>
		class OnlyLastMessageBuffer : public MessageBuffer<MessageClass>
		{
		public:
			template <typename MessageProcessorOwnerClass>
			OnlyLastMessageBuffer(MessageProcessorOwnerClass *message_processor, void (MessageProcessorOwnerClass::*message_process_callback)(const MessageClass&)):
			MessageBuffer<MessageClass>( std::bind(message_process_callback, message_processor, std::placeholders::_1) ){}
			
			OnlyLastMessageBuffer(std::function<void(const MessageClass&)> process_message_callback):
			MessageBuffer<MessageClass>(process_message_callback){}

			OnlyLastMessageBuffer(const OnlyLastMessageBuffer& rhs) :
			MessageBuffer<MessageClass>( static_cast<const MessageBuffer<MessageClass>&>(rhs) ){}

			virtual void flush()
			{
				std::lock_guard<std::mutex> guard(message_guard_mutex);
				if(accumulated_message)
				{
					this->process_message_callback(*accumulated_message);
					accumulated_message.reset();
				}
			}

		protected:
			virtual void pushConcreteMessage(const MessageClass& message)
			{
				std::lock_guard<std::mutex> guard(message_guard_mutex);
				accumulated_message.reset(new MessageClass(message));
			}
			
		private:
			std::mutex message_guard_mutex;
			std::shared_ptr<MessageClass> accumulated_message;
		};
	}
}