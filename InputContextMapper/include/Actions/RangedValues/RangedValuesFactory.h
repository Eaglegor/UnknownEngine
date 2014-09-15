#pragma once

#include <Actions/RangedValues/IRangedValue.h>
#include <Scalar.h>
#include <memory>

namespace UnknownEngine
{
	namespace IO
	{
		class RangedValuesFactory
		{
		public:
			static std::unique_ptr<IRangedValue> createRangedValue(IRangedValue::UpdateValueSemantics update_value_semantics, Math::Scalar valueable_range_delta = Math::ZERO_PRECISION);
		};
	}
}