#include <Actions/SimpleSingleEventAction.h>

namespace UnknownEngine
{
	namespace IO
	{
		SimpleSingleEventAction::SimpleSingleEventAction( const CallbackType &reactor ):
		event_active(false),
		reactor(reactor)
		{
		}

		SimpleSingleEventAction::~SimpleSingleEventAction()
		{

		}

		void SimpleSingleEventAction::onEventStarted()
		{
			event_active = true;
		}

		void SimpleSingleEventAction::onEventEnded()
		{

		}

		void SimpleSingleEventAction::perform()
		{
			if(event_active)
			{
				reactor();
				event_active = false;
			}
		}

		void SimpleSingleEventAction::reset()
		{
			event_active = false;
		}
	}
}
