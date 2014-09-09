#pragma once

#include <string>
#include <DataProvider/DataProviderType.h>
#include <Properties/Properties.h>
#include <DescriptorContainer.h>
#include <Properties/Properties_fwd.h>
#include <boost/variant.hpp>

namespace UnknownEngine
{
	namespace Loader
	{
		/// Descriptor of data provider to be created by the factory
		struct DataProviderDesc
		{
			std::string name; ///< Data provider name
			DataProviderType type; ///< Data provider type
			boost::variant<Core::DescriptorContainer, Core::Properties> descriptor;
		};

	}
}
