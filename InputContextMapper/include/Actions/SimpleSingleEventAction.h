#pragma once

#include <Actions/SimpleAction.h>
#include <functional>

namespace UnknownEngine
{
	namespace IO
	{
		class SimpleSingleEventAction : public SimpleAction
		{
		public:
			SimpleSingleEventAction(std::function<void()> reactor);
			virtual ~SimpleSingleEventAction();
			
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