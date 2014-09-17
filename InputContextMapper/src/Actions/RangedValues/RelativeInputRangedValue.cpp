#include <Actions/RangedValues/RelativeInputRangedValue.h>
#include <cmath>

namespace UnknownEngine
{
	namespace IO
	{
		RelativeInputRangedValue::RelativeInputRangedValue(Math::Scalar valueable_delta):
		BaseRangedValue(IRangedValue::ValueSemantics::RELATIVE, valueable_delta)
		{
		}

		RelativeInputRangedValue::~RelativeInputRangedValue()
		{
		}

		void RelativeInputRangedValue::updateValue(Math::Scalar value)
		{
			if(std::fabs(value) > valueable_delta)
			{
				delta_value += value;
				absolute_value += value;
				delta_changed = true;
			}
		}
	}
}