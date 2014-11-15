#pragma once

#include <queue>
#include <mutex>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		class LockingConcurrentQueue
		{
		private:
			typedef std::mutex LockPrimitive;
			
		public:
			bool try_pop(T& out_value)
			{
				std::lock_guard<LockPrimitive> guard(lock);
				if(internal_queue.empty()) return false;
				out_value = internal_queue.front();
				internal_queue.pop();
				return true;
			}
			
			void push(const T& value)
			{
				std::lock_guard<LockPrimitive> guard(lock);
				internal_queue.push(value);
			}
			
		private:
			std::queue<T> internal_queue;
			LockPrimitive lock;
			
		};
	}
}