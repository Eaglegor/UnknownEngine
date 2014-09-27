#pragma once

#include <ActionConditions/ActionCondition.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		class EventStateChangedCondition : public ActionCondition
		{
		public:
			EventStateChangedCondition(bool on_event_start);
			
			virtual bool isTrue();
			virtual void update ( bool event_started );
			
		private:
			bool is_true;
			bool is_used;
			bool on_event_start;
		};
		
		class EventStartedCondition : public EventStateChangedCondition
		{
		public:
			EventStartedCondition():EventStateChangedCondition(true){}
		};
		
		class EventEndedCondition : public EventStateChangedCondition
		{
		public:
			EventEndedCondition():EventStateChangedCondition(false){}
		};
		
	}
}