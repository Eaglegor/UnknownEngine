#pragma once

#include <string>
#include <DataProvider/DataProviderType.h>
#include <Properties/Properties.h>
#include <DescriptorContainer.h>
#include <Properties/Properties_fwd.h>

namespace UnknownEngine
{
	namespace Loader
	{
		/// Descriptor of data provider to be created by the factory
		struct DataProviderDesc
		{
			std::string name; ///< Data provider name
			DataProviderType type; ///< Data provider type
			Core::DescriptorContainer descriptor; ///< Descriptor of concrete data provider. Check if it's set to avoid parsing
			Core::Properties creation_options; ///< String representation of options. Parse if descriptor isn't set
		};

	}
}
