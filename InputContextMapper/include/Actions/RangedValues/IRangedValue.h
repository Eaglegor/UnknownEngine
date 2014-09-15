#pragma once

#include <Scalar.h>

namespace UnknownEngine
{
	namespace IO
	{
		class IRangedValue
		{
		public:
			enum class UpdateValueSemantics
			{
				RELATIVE, ///< Value passed to updateValue is a delta from previous value
				ABSOLUTE ///< Value passed to updateValue is the new absolute value
			};
			
			virtual bool hasUsefulValue() const = 0;
			virtual Math::Scalar getRelativeValue() const = 0;
			virtual Math::Scalar getAbsoluteValue() const = 0;
			virtual void reset(Math::Scalar new_absolute_value = 0) = 0;
			virtual void updateValue(Math::Scalar value) = 0;
		};
	}
}