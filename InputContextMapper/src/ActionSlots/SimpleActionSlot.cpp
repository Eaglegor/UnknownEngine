#include <stdafx.h>
#include <ActionConditions/EventActiveCondition.h>
#include <ActionConditions/EventStateChangedCondition.h>
#include <ActionSlots/SimpleActionSlot.h>
#include <InputContext.h>

#include <iostream>

namespace UnknownEngine
{
	namespace IO
	{

		SimpleActionSlot::SimpleActionSlot(InputContext* context, const SimpleActionSlot::ConditionType& condition_type ):
		context(context)
		{
			switch(condition_type)
			{
				case ConditionType::EVENT_STARTED:
				{
					condition.reset ( new EventStartedCondition() );
					break;
				}
				case ConditionType::EVENT_ACTIVE:
				{
					condition.reset ( new EventActiveCondition() );
					break;
				}
				case ConditionType::EVENT_ENDED:
				{
					condition.reset ( new EventEndedCondition() );
					break;
				}
			}
		}

		SimpleActionSlot::~SimpleActionSlot()
		{
		}
		
		void SimpleActionSlot::setAction ( ActionType action )
		{
			this->action = action;
		}

		void SimpleActionSlot::reset()
		{
			this->action = ActionType();
		}
		
		void SimpleActionSlot::onEvent(bool event_started)
		{
			if(condition) 
			{
				condition->update(event_started);
			}
		}

		void SimpleActionSlot::update()
		{
			if(action && condition && condition->isTrue())
			{
				action();
			}
		}

		bool SimpleActionSlot::isActive()
		{
			return context->isActive();
		}
		
	}
}