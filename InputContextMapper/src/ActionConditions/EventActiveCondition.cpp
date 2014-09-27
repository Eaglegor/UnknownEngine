#include <ActionConditions/EventActiveCondition.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		EventActiveCondition::EventActiveCondition ()
		{
		}

		bool EventActiveCondition::isTrue()
		{
			return is_active;
		}

		void EventActiveCondition::update ( bool event_started )
		{
			is_active = event_started;
		}
	}
}