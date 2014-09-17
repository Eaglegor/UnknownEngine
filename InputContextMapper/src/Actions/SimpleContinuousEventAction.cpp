#include <Actions/SimpleContinuousEventAction.h>

namespace UnknownEngine
{
	namespace IO
	{
		SimpleContinuousAction::SimpleContinuousAction( const CallbackType& reactor ):
		event_active(false),
		reactor(reactor)
		{
		}

		SimpleContinuousAction::~SimpleContinuousAction()
		{

		}

		void SimpleContinuousAction::onEventStarted()
		{
			event_active = true;
		}

		void SimpleContinuousAction::onEventEnded()
		{
			event_active = false;
		}

		void SimpleContinuousAction::perform()
		{
			if(event_active)
			{
				reactor();
			}
		}

		void SimpleContinuousAction::reset()
		{
			event_active = false;
		}
	}
}
