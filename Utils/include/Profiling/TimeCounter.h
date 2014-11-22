#pragma once

#include <Scalar.h>
#include <chrono>

namespace UnknownEngine
{
	namespace Utils
	{
		class TimeCounter
		{
		public:
			TimeCounter():
			dt(0),
			elapsed(0)
			{}
			
			Math::Scalar getDt()
			{
				return dt;
			}
			
			void resetElapsedTime()
			{
				elapsed = 0;
			}
			
			Math::Scalar getElapsedTime()
			{
				return elapsed;
			}
			
			void tick()
			{
				std::chrono::steady_clock::time_point newTime = std::chrono::steady_clock::now();
				dur = newTime - old;
				old = newTime;
				dt = dur.count();
				elapsed += dt;
			}
			
		private:
			Math::Scalar dt;
			Math::Scalar elapsed;
			std::chrono::duration<float> dur;
			std::chrono::steady_clock::time_point old;
		};
	}
}