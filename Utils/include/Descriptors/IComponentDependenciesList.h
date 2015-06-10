#pragma once

#include <vector>


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
				virtual IComponentDependenciesList& operator=(const std::vector<std::string>& props) = 0;
		};
	}
}
