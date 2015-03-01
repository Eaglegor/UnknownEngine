#pragma once

#include <functional>
#include <memory>
#include <ActionConditions/ActionCondition.h>

namespace UnknownEngine
{
	namespace IO
	{
		class SimpleActionSlot
		{
		public:
			typedef std::function<void()> ActionType;
			
			enum class ConditionType
			{
				EVENT_STARTED,
				EVENT_ACTIVE,
				EVENT_ENDED
			};
			
			SimpleActionSlot(const ConditionType &condition_type);
			~SimpleActionSlot();
			
			void update();
			
			void setAction(ActionType action);
			void reset();
			
			void onEvent(bool event_started);
			
		private:
			ActionType action;
			std::shared_ptr<ActionCondition> condition;
			
		};
	}
}