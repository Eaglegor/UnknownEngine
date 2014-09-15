#pragma once

#include <Actions/SimpleAction.h>
#include <functional>

namespace UnknownEngine
{
	namespace IO
	{
		class SimpleContinuousAction : public SimpleAction
		{
		public:
			SimpleContinuousAction(const std::function<void()> &reactor);
			virtual ~SimpleContinuousAction();
			
			void onEventStarted();
			void onEventEnded();
			
			void perform();
			void reset();
			
		private:
			bool event_active;
			std::function<void()> reactor;
		};
	}
}