#pragma once

#include <Properties/Properties.h>
#include <vector>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename T>
		class IDescriptorsList
		{
			public:
				virtual bool isValid() = 0;
				virtual const std::vector< T >& get() = 0;
				virtual IDescriptorsList<T>& operator=(const std::vector<Core::Properties>& props) = 0;
		};
	}
}
