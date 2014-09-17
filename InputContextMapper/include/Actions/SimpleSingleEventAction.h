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
			SimpleSingleEventAction(const CallbackType &reactor);
			virtual ~SimpleSingleEventAction();
			
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