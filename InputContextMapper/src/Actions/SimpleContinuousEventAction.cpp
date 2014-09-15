#include <Actions/SimpleContinuousEventAction.h>

namespace UnknownEngine
{
	namespace IO
	{
		SimpleContinuousAction::SimpleContinuousAction( const std::function< void() >& reactor ):
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
	}
}
