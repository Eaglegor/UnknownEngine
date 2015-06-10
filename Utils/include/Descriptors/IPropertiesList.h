#pragma once

#include <vector>

namespace UnknownEngine
{
	namespace Utils
	{
		class IPropertiesList
		{
			public:
				virtual bool isValid() = 0;
				virtual IPropertiesList<T>& operator=(const std::vector<std::string>& props) = 0;
		};
	}
}
