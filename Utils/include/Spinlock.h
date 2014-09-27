#pragma once

#include <atomic>

namespace UnknownEngine
{
	namespace Utils
	{
		class Spinlock
		{
		public:
			Spinlock()
#ifndef _MSC_VER
			:spinlock(ATOMIC_FLAG_INIT)
#endif
			{
#ifdef _MSC_VER
				spinlock.clear();
#endif
			}

			void lock()
			{
				while(spinlock.test_and_set(std::memory_order_acquire));
			}
			
			void unlock()
			{
				spinlock.clear(std::memory_order_release);
			}
			
		private:
			std::atomic_flag spinlock;
		};
	}
}