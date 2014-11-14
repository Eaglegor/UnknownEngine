#pragma once

#include <queue>
#include <mutex>
#include <Spinlock.h>
#include <MessageBuffers/MessageBuffer.h>

#include <iostream>

namespace UnknownEngine
{
	namespace Utils
	{
		template <typename MessageClass>
		class QueuedMessageBuffer : public MessageBuffer<MessageClass>
		{
		public:
			template <typename MessageProcessorOwnerClass>
			QueuedMessageBuffer(MessageProcessorOwnerClass *message_processor, void (MessageProcessorOwnerClass::*message_process_callback)(const MessageClass&)):
			MessageBuffer<MessageClass>( std::bind(message_process_callback, message_processor, std::placeholders::_1) ){}
			
			QueuedMessageBuffer(std::function<void(const MessageClass&)> process_message_callback):
			MessageBuffer<MessageClass>(process_message_callback){}
			
			QueuedMessageBuffer(const QueuedMessageBuffer& rhs) :
			MessageBuffer<MessageClass>(static_cast<const MessageBuffer<MessageClass>&>(rhs)){}

			virtual void flush()
			{
				std::unique_lock<Spinlock> guard( queue_spinlock );
				while(!message_queue.empty())
				{
					MessageClass msg = message_queue.front();
					message_queue.pop();
					guard.unlock();
					this->process_message_callback(msg);
					guard.lock();
				}
			}
			
		protected:
			virtual void pushConcreteMessage(const MessageClass& message)
			{
				std::unique_lock<Spinlock> guard( queue_spinlock );
				message_queue.push(message);
			}
			
		private:
			std::queue<MessageClass> message_queue;
			Spinlock queue_spinlock;
			
		};
	}
}