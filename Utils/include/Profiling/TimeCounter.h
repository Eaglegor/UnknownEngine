#pragma once

#include <chrono>

namespace UnknownEngine
{
	namespace Utils
	{
		class TimeCounter
		{
		public:
			float getDt()
			{
				return dt;
			}
			
			void tick()
			{
				std::chrono::steady_clock::time_point newTime = std::chrono::steady_clock::now();
				dur += newTime - old;
				old = newTime;
				dt = dur.count();
				dur = dur.zero();
			}
			
		private:
			float dt;
			std::chrono::duration<float> dur;
			std::chrono::steady_clock::time_point old;
		};
	}
}