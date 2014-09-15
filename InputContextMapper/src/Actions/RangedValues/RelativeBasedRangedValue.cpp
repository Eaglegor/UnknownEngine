#include <Actions/RangedValues/RelativeBasedRangedValue.h>

namespace UnknownEngine
{
	namespace IO
	{
		RelativeBasedRangedValue::RelativeBasedRangedValue(Math::Scalar valueable_delta):
		valueable_delta(valueable_delta),
		value(0),
		delta(0)
		{

		}

		RelativeBasedRangedValue::~RelativeBasedRangedValue()
		{

		}

		Math::Scalar RelativeBasedRangedValue::getAbsoluteValue() const
		{
			return value;
		}

		Math::Scalar RelativeBasedRangedValue::getRelativeValue() const
		{
			return delta;
		}

		void RelativeBasedRangedValue::reset( Math::Scalar new_absolute_value )
		{
			value = new_absolute_value;
			delta = 0;
		}

		void RelativeBasedRangedValue::updateValue ( Math::Scalar value )
		{
			if(value > valueable_delta)
			{
				delta += value;
				this->value += value;
			}
		}
		
		bool RelativeBasedRangedValue::hasUsefulValue() const
		{
			return delta > valueable_delta;
		}

	}
}