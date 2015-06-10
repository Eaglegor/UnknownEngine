#pragma once

#include <vector>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		class IPropertiesList
		{
			public:
				virtual bool isValid() = 0;
				virtual const std::vector< T >& get() = 0;
				virtual IPropertiesList<T>& operator=(const std::vector<std::string>& props) = 0;
		};
	}
}
