#pragma once

#include <ActionConditions/ActionCondition.h>

namespace UnknownEngine
{
	namespace IO
	{
		class EventActiveCondition : public ActionCondition
		{
		public:
			EventActiveCondition();
			
			virtual bool isTrue();
			
			virtual void update ( bool event_started );
			
		private:
			bool is_active;
		};
	}
}