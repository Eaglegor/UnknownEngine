#pragma once

#include <Descriptors/ComponentDependency.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		using OptionalComponentDependency = ComponentDependency<IProperty::OPTIONAL>;
	}
}
