#pragma once

#include <Actions/RangedAction.h>
#include <Actions/RangedValues/IRangedValue.h>
#include <functional>
#include <memory>

namespace UnknownEngine
{
	namespace IO
	{
		class RangedContinuousEventAction : public RangedAction
		{
		public:
			RangedContinuousEventAction(const std::function<void(Math::Scalar)> &reactor, Math::Scalar valueable_range_delta = Math::ZERO_PRECISION);
			virtual ~RangedContinuousEventAction();
			void onEvent(Math::Scalar new_value);
			
			void perform() override;
			void reset() override;
			
		private:
			std::unique_ptr<IRangedValue> value;
			std::function<void(Math::Scalar)> reactor;
		};
	}
}