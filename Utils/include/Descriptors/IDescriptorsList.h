#pragma once

#include <Properties/Properties.h>
#include <vector>

namespace UnknownEngine
{
	namespace Utils
	{
		class IDescriptorsList
		{
			public:
				virtual bool isValid() = 0;
				virtual IDescriptorsList<T>& operator=(const std::vector<Core::Properties>& props) = 0;
		};
	}
}
