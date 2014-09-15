#include <Actions/RangedValues/RangedValuesFactory.h>
#include <Actions/RangedValues/AbsoluteBasedRangedValue.h>
#include <Actions/RangedValues/RelativeBasedRangedValue.h>

namespace UnknownEngine 
{
	namespace IO
	{
		std::unique_ptr< IRangedValue > RangedValuesFactory::createRangedValue ( IRangedValue::UpdateValueSemantics update_value_semantics, Math::Scalar valueable_range_delta )
		{
			switch(update_value_semantics)
			{
				case IRangedValue::UpdateValueSemantics::ABSOLUTE:
				{
					return std::move( std::unique_ptr<IRangedValue>( new AbsoluteBasedRangedValue(valueable_range_delta) ) );
				}
				case IRangedValue::UpdateValueSemantics::RELATIVE:
				{
					return std::move( std::unique_ptr<IRangedValue>( new AbsoluteBasedRangedValue(valueable_range_delta) ) );
				}
			}
		}
	}
}