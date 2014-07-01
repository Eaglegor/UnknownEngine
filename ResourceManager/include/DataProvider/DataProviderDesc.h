#pragma once

#include <string>
#include <DataProvider/DataProviderType.h>
#include <Properties/Properties.h>

namespace UnknownEngine
{
	namespace Loader
	{
		struct DataProviderDesc
		{
			std::string name;
			DataProviderType type;
			Core::Properties properties;
		};
	}
}
