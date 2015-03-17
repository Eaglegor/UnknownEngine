#pragma once

#include <Profiling/TimeCounter.h>
#include <functional>
#include <iostream>
namespace UnknownEngine
{
	namespace Utils
	{
		class AverageFpsCounter
		{
		public:
			
			typedef std::function<void(size_t)> FpsReturnPolicy;
			
			AverageFpsCounter(size_t frames_count, FpsReturnPolicy return_policy):
			counter(0),
			frames_count(frames_count),
			return_policy(return_policy)
			{
			}
			
			void nextFrame()
			{
				++counter;
				if(counter == frames_count)
				{
					timer.tick();
					if(timer.getDt() > 0)
					{
						size_t fps = static_cast<size_t>( 1 / (timer.getDt() / static_cast<float>(counter)) );
						return_policy(fps);
					}
					counter = 0;
				}
			}
			
		private:
			size_t counter;
			size_t frames_count;
			TimeCounter timer;
			FpsReturnPolicy return_policy;
		};
	}
}