#pragma once

#include <Descriptors/NestedDescriptorsList.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		using RequiredDescriptorsList = DescriptorsList<T, IProperty::REQUIRED_PROPERTY>;
	}
}
