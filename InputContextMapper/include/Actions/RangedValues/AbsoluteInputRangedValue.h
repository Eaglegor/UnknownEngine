#pragma once

#include <Actions/RangedValues/BaseRangedValue.h>

namespace UnknownEngine
{
	namespace IO
	{
		class AbsoluteInputRangedValue : public BaseRangedValue
		{
		public:
			AbsoluteInputRangedValue(Math::Scalar valueable_delta);
			~AbsoluteInputRangedValue();

			virtual void updateValue(Math::Scalar value) override;
		};
	}
}