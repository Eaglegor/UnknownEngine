#include <Actions/RangedValues/BaseRangedValue.h>
#include <cmath>

namespace UnknownEngine
{
	namespace IO
	{
		BaseRangedValue::BaseRangedValue(IRangedValue::ValueSemantics input_semantics, Math::Scalar valueable_delta) :
				absolute_value(0),
				delta_value(0),
				valueable_delta(valueable_delta),
				input_semantics(input_semantics)
		{
		}

		BaseRangedValue::~BaseRangedValue()
		{
		}

		Math::Scalar BaseRangedValue::getValue(IRangedValue::ValueSemantics output_semantics) const
		{
			switch (output_semantics) {
				case IRangedValue::ValueSemantics::ABSOLUTE: {
					return absolute_value;
				}
				case IRangedValue::ValueSemantics::RELATIVE: {
					return delta_value;
				}
			}
		}

		void BaseRangedValue::reset(Math::Scalar new_absolute_value)
		{
			absolute_value = new_absolute_value;
			reset();
		}

		void BaseRangedValue::reset()
		{
			delta_value = 0;
			delta_changed = false;
		}

		bool BaseRangedValue::empty(IRangedValue::ValueSemantics output_semantics) const
		{
			switch (output_semantics) {
				case IRangedValue::ValueSemantics::ABSOLUTE: {
					return false;
				}
				case IRangedValue::ValueSemantics::RELATIVE: {
					return !delta_changed;
				}
			}
		}

	}
}