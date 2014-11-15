#pragma once

#include <condition_variable>
#include <mutex>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename LockPrimitive>
		class BasicWaitingForEventWrapper
		{
		public:
			
			BasicWaitingForEventWrapper():
			event_happened(false)
			{}
			
			void notify()
			{
				std::unique_lock<LockPrimitive> lock(event_mutex);
				event_happened = true;
				wait_for_event_var.notify_all();
			}
			
			void wait()
			{
				std::unique_lock<LockPrimitive> lock(event_mutex);
				while(!event_happened)
				{
					wait_for_event_var.wait(lock);
				}
			}
			
		private:
			volatile bool event_happened;
			std::condition_variable wait_for_event_var;
			LockPrimitive event_mutex;
		};
		
		typedef BasicWaitingForEventWrapper<std::mutex> WaitingForEventWrapper;
	}
}