#pragma once

#include <Descriptors/PropertiesList.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		using RequiredPropertiesList = PropertiesList<T, IProperty::REQUIRED_PROPERTY>;
	}
}
