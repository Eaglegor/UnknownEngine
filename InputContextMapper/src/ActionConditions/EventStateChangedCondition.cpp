#include <stdafx.h>
#include <ActionConditions/EventStateChangedCondition.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		EventStateChangedCondition::EventStateChangedCondition(bool on_event_start):
		is_true(false),
		is_used(false),
		on_event_start(on_event_start)
		{
		}
		
		void EventStateChangedCondition::update ( bool event_started )
		{
			if(event_started == on_event_start)
			{
				if(!is_used)
				{
					is_true = true;
				}
			}
			else
			{
				if(is_used)
				{
					is_used = false;
					is_true = false;
				}
			}
		}
		
		bool EventStateChangedCondition::isTrue()
		{
			if(!is_used && is_true)
			{
				is_used = true;
				is_true = false;
				return true;
			}

			return false;
		}
		
	}
}