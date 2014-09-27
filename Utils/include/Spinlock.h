#pragma once

#include <atomic>

namespace UnknownEngine
{
	namespace Utils
	{
		class Spinlock
		{
		public:
			Spinlock():spinlock(ATOMIC_FLAG_INIT){}

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