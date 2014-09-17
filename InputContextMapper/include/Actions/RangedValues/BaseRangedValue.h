#pragma once

#include <Actions/RangedValues/IRangedValue.h>

namespace UnknownEngine
{
	namespace IO
	{

		class BaseRangedValue : public IRangedValue
		{
		public:
			BaseRangedValue(IRangedValue::ValueSemantics input_semantics, Math::Scalar valueable_delta);
			virtual ~BaseRangedValue();
			Math::Scalar getValue(IRangedValue::ValueSemantics output_semantics) const override;
			void reset(Math::Scalar new_absolute_value) override;
			void reset() override;
			bool empty(IRangedValue::ValueSemantics output_semantics) const override;
			
		protected:
			Math::Scalar absolute_value;
			Math::Scalar delta_value;
			Math::Scalar valueable_delta;
			IRangedValue::ValueSemantics input_semantics;
			bool delta_changed;
		};
	}
}