#pragma once

#include <vector>
#include <Descriptors/RequiredProperty.h>


namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}

	namespace Utils
	{
		class IComponentDependenciesList
		{
			public:
				virtual bool isValid() = 0;
				virtual const std::vector< Core::IComponent* >& get() = 0;
				virtual IComponentDependenciesList& operator=(const std::vector<std::string>& props) = 0;
		};
	}
}
