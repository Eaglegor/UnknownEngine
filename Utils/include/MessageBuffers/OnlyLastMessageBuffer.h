#pragma once

#include <boost/optional.hpp>
#include <boost/thread.hpp>
#include <MessageBuffers/MessageBuffer.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template <typename MessageClass>
		class OnlyLastMessageBuffer : public MessageBuffer<MessageClass>
		{
		public:
			OnlyLastMessageBuffer(std::function<void(const MessageClass&)> flush_callback):
			MessageBuffer<MessageClass>(flush_callback){}
			
			virtual void flush()
			{
				boost::lock_guard<boost::mutex> guard(message_guard_mutex);
				if(accumulated_message)
				{
					this->flush_callback(accumulated_message.get());
					accumulated_message = boost::none;
				}
			}

		protected:
			virtual void pushConcreteMessage(const MessageClass& message)
			{
				boost::lock_guard<boost::mutex> guard(message_guard_mutex);
				accumulated_message = message;
			}
			
		private:
			boost::mutex message_guard_mutex;
			boost::optional<MessageClass> accumulated_message;
		};
	}
}