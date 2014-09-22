#include <ActionSlots/RangeActionSlot.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		RangeActionSlot::RangeActionSlot():
		current_state(0)
		{
		}
		
		RangeActionSlot::~RangeActionSlot()
		{
		}
		
		void RangeActionSlot::onEvent ( Math::Scalar new_state )
		{
			current_state = new_state;
		}

		void RangeActionSlot::setAction ( RangeActionSlot::ActionType action )
		{
			this->action = action;
		}

		void RangeActionSlot::update()
		{
			action(current_state);
		}

	}
}