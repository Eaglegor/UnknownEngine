#include <Actions/RangedValues/RangedValuesFactory.h>
#include <Actions/RangedValues/AbsoluteInputRangedValue.h>
#include <Actions/RangedValues/RelativeInputRangedValue.h>

namespace UnknownEngine 
{
	namespace IO
	{
		std::unique_ptr< IRangedValue > RangedValuesFactory::createRangedValue ( IRangedValue::ValueSemantics input_value_semantics, Math::Scalar valueable_range_delta )
		{
			switch(input_value_semantics)
			{
				case IRangedValue::ValueSemantics::ABSOLUTE:
				{
					return std::move( std::unique_ptr<IRangedValue>( new AbsoluteInputRangedValue(valueable_range_delta) ) );
				}
				case IRangedValue::ValueSemantics::RELATIVE:
				{
					return std::move( std::unique_ptr<IRangedValue>( new RelativeInputRangedValue(valueable_range_delta) ) );
				}
			}
		}
	}
}