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
			InstantForwardMessageBuffer(std::function<void(const MessageClass&)> process_message_callback):
			MessageBuffer<MessageClass>(process_message_callback){}
			
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