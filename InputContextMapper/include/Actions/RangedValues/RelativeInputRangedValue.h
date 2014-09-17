#pragma once

#include <Actions/RangedValues/BaseRangedValue.h>

namespace UnknownEngine
{
	namespace IO
	{
		class RelativeInputRangedValue : public BaseRangedValue
		{
		public:
			RelativeInputRangedValue(Math::Scalar valueable_delta);
			~RelativeInputRangedValue();

			virtual void updateValue(Math::Scalar value) override;
		};
	}
}