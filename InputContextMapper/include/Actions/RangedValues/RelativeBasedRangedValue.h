#pragma once

#include <Actions/RangedValues/IRangedValue.h>

namespace UnknownEngine
{
	namespace IO
	{
		class RelativeBasedRangedValue : public IRangedValue
		{
		public:
			RelativeBasedRangedValue(Math::Scalar valueable_delta);
			virtual ~RelativeBasedRangedValue();
			Math::Scalar getRelativeValue() const override;
			Math::Scalar getAbsoluteValue() const override;
			void reset(Math::Scalar new_absolute_value) override;
			void updateValue(Math::Scalar value) override;
			bool hasUsefulValue() const override;
			
		private:
			const Math::Scalar valueable_delta;
			Math::Scalar value;
			Math::Scalar delta;
		};
	}
}