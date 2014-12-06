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
		struct DataProviderDesc
		{
			std::string name;
			DataProviderType type;
			boost::variant<Core::DescriptorContainer, Core::Properties> descriptor;
		};

	}
}
