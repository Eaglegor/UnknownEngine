#pragma once

#include <tbb/concurrent_queue.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		class TBBConcurrentQueue
		{
		public:
			bool try_pop(T& out_value)
			{
				internal_queue.try_pop(out_value);
			}
			
			void push(const T& value)
			{
				internal_queue.push(value);
			}
			
		private:
			tbb::concurrent_queue internal_queue;
			
		};
	}
}