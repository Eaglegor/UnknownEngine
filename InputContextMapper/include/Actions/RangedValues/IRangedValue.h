#pragma once

#include <Scalar.h>

namespace UnknownEngine
{
	namespace IO
	{
		class IRangedValue
		{
		public:
			enum class ValueSemantics
			{
				RELATIVE, ///< Value passed to updateValue is a delta from previous value
				ABSOLUTE ///< Value passed to updateValue is the new absolute value
			};
			
			virtual bool empty(IRangedValue::ValueSemantics output_semantics) const = 0;
			virtual Math::Scalar getValue(IRangedValue::ValueSemantics output_semantics) const = 0;
			virtual void reset(Math::Scalar new_absolute_value) = 0;
			virtual void reset() = 0;
			virtual void updateValue(Math::Scalar value) = 0;
		};
	}
}