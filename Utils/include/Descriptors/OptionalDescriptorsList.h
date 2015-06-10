#pragma once

#include <Descriptors/NestedDescriptorsList.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		using OptionalDescriptorsList = DescriptorsList<T, IProperty::OPTIONAL_PROPERTY>;
	}
}
