#pragma once

#include <Descriptors/Property.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		using RequiredProperty = Property<T, IProperty::REQUIRED>;
	}
}