#include <Actions/RangedValues/AbsoluteInputRangedValue.h>
#include <cmath>

namespace UnknownEngine
{
	namespace IO
	{
		AbsoluteInputRangedValue::AbsoluteInputRangedValue(Math::Scalar valueable_delta):
				BaseRangedValue(IRangedValue::ValueSemantics::ABSOLUTE, valueable_delta)
		{
		}

		AbsoluteInputRangedValue::~AbsoluteInputRangedValue()
		{
		}

		void AbsoluteInputRangedValue::updateValue(Math::Scalar value)
		{
			Math::Scalar delta = value - absolute_value;
			if(std::fabs(delta) > valueable_delta)
			{
				delta_value += delta;
				absolute_value = value;
				delta_changed = true;
			}
		}
	}
}