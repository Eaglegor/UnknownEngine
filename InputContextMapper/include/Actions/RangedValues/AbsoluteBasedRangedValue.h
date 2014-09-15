#pragma once

#include <Actions/RangedValues/IRangedValue.h>

namespace UnknownEngine
{
	namespace IO
	{
		class AbsoluteBasedRangedValue : public IRangedValue
		{
		public:
			AbsoluteBasedRangedValue(Math::Scalar valueable_delta);
			virtual ~AbsoluteBasedRangedValue();
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