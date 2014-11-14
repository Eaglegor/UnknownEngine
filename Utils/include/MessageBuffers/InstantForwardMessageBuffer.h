#pragma once

#include <boost/optional.hpp>
#include <boost/thread.hpp>
#include <MessageBuffers/MessageBuffer.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template <typename MessageClass>
		class InstantForwardMessageBuffer : public MessageBuffer<MessageClass>
		{
		public:
			template <typename MessageProcessorOwnerClass>
			InstantForwardMessageBuffer(MessageProcessorOwnerClass *message_processor, void (MessageProcessorOwnerClass::*message_process_callback)(const MessageClass&)):
			MessageBuffer<MessageClass>( std::bind(message_process_callback, message_processor, std::placeholders::_1) ){}
			
			InstantForwardMessageBuffer(std::function<void(const MessageClass&)> process_message_callback):
			MessageBuffer<MessageClass>(process_message_callback){}
			
			InstantForwardMessageBuffer(const InstantForwardMessageBuffer& rhs):
			MessageBuffer<MessageClass>(static_cast<const MessageBuffer<MessageClass>&>(rhs)){}

			virtual void flush()
			{}

		protected:
			virtual void pushConcreteMessage(const MessageClass& message)
			{
				boost::lock_guard<boost::mutex> guard(message_guard_mutex);
				this->process_message_callback(message);
			}
			
		private:
			boost::mutex message_guard_mutex;
		};
	}
}