#include <Actions/RangedSingleEventAction.h>

namespace UnknownEngine
{
	namespace IO
	{
		RangedSingleEventAction::RangedSingleEventAction( const std::function< void(Math::Scalar) >& reactor, Math::Scalar valueable_range_delta):
		reactor(reactor)
		{
			
		}

		RangedSingleEventAction::~RangedSingleEventAction()
		{
		}

		void RangedSingleEventAction::onEvent ( float new_value )
		{
			value->updateValue(new_value);
		}

		void RangedSingleEventAction::perform()
		{
			if(!value->empty(IRangedValue::ValueSemantics::RELATIVE))
			{
				reactor(value->getValue(IRangedValue::ValueSemantics::RELATIVE));
				value->reset(value->getValue(IRangedValue::ValueSemantics::ABSOLUTE));
			}
		}

		void RangedSingleEventAction::reset()
		{
			value->reset();
		}
	}
}
