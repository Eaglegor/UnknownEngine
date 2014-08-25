#pragma once

#include <boost/lockfree/queue.hpp>
#include <MessageBuffers/MessageBuffer.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template <typename MessageClass, size_t FixedSize>
		class FixedSizeQueuedMessageBuffer : public MessageBuffer<MessageClass>
		{
		public:
			FixedSizeQueuedMessageBuffer(std::function<void(const MessageClass&)> flush_callback):
			MessageBuffer<MessageClass>(flush_callback){}
			
			virtual void flush()
			{
				MessageClass message;
				while(messages_queue.pop(message))
				{
					this->flush_callback(message);
				}
			}
			
		protected:
			virtual void pushConcreteMessage(const MessageClass& message)
			{
				messages_queue.push(message);
			}
			
		private:
			boost::lockfree::queue<MessageClass, boost::lockfree::fixed_sized<true>, boost::lockfree::capacity<FixedSize>> messages_queue;
			
		};
	}
}