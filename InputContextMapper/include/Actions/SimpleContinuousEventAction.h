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
			SimpleContinuousAction(const CallbackType &reactor);
			virtual ~SimpleContinuousAction();
			
			void onEventStarted();
			void onEventEnded();
			
			void perform() override;
			void reset() override;
			
		private:
			bool event_active;
			CallbackType reactor;
		};
	}
}