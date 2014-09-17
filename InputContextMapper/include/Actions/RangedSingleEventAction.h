#pragma once

#include <Actions/RangedAction.h>
#include <functional>
#include <Actions/RangedValues/IRangedValue.h>
#include <memory>

namespace UnknownEngine
{
	namespace IO
	{
		class RangedSingleEventAction : public RangedAction
		{
		public:
			RangedSingleEventAction(const std::function<void(Math::Scalar)> &reactor, Math::Scalar valueable_range_delta = Math::ZERO_PRECISION);
			virtual ~RangedSingleEventAction();
			
			void onEvent(Math::Scalar new_value);
			
			void perform() override;
			void reset() override;
			
		private:
			std::unique_ptr<IRangedValue> value;
			std::function<void(Math::Scalar)> reactor;
		};
	}
}