#pragma once

#include <Descriptors/Property.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		using OptionalProperty = Property<T, IProperty::OPTIONAL_PROPERTY>;
	}
}