#pragma once

#include <string>
#include <DataProvider/DataProviderType.h>
#include <Properties/Properties.h>

namespace UnknownEngine
{
	namespace Loader
	{
		/// Descriptor of data provider to be created by the factory
		struct DataProviderDesc
		{
			std::string name; ///< Data provider name
			DataProviderType type; ///< Data provider type
			Core::Properties properties; ///< Settings of data provider
		};
	}
}
