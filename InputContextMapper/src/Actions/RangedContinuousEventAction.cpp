#include <Actions/RangedContinuousEventAction.h>

namespace UnknownEngine
{
	namespace IO
	{
		RangedContinuousEventAction::RangedContinuousEventAction(const std::function<void(Math::Scalar)> &reactor, Math::Scalar valueable_range_delta):
		reactor(reactor)
		{
		}

		RangedContinuousEventAction::~RangedContinuousEventAction()
		{

		}

		void RangedContinuousEventAction::onEvent ( float new_value )
		{
			value->updateValue(new_value);
		}

		void RangedContinuousEventAction::perform()
		{
			reactor(value->getAbsoluteValue());
		}
	}
}
