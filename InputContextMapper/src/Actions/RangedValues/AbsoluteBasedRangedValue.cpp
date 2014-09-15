#include <Actions/RangedValues/AbsoluteBasedRangedValue.h>

namespace UnknownEngine
{
	namespace IO
	{
		AbsoluteBasedRangedValue::AbsoluteBasedRangedValue(Math::Scalar valueable_delta):
		valueable_delta(valueable_delta),
		value(0),
		delta(0)
		{
		}

		AbsoluteBasedRangedValue::~AbsoluteBasedRangedValue()
		{

		}

		Math::Scalar AbsoluteBasedRangedValue::getAbsoluteValue() const
		{
			return value;
		}

		Math::Scalar AbsoluteBasedRangedValue::getRelativeValue() const
		{
			return delta;
		}

		void AbsoluteBasedRangedValue::reset( Math::Scalar new_absolute_value )
		{
			value = new_absolute_value;
			delta = 0;
		}

		void AbsoluteBasedRangedValue::updateValue ( Math::Scalar value )
		{
			Math::Scalar new_delta = (value - this->value);
			if(new_delta > valueable_delta)
			{
				delta += new_delta;
				this->value = value;
			}
		}
		
		bool AbsoluteBasedRangedValue::hasUsefulValue() const
		{
			return true;
		}

	}
}