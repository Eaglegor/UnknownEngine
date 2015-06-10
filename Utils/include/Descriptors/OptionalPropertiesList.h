#pragma once

#include <Descriptors/PropertiesList.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		using OptionalPropertiesList = PropertiesList<T, IProperty::OPTIONAL_PROPERTY>;
	}
}
