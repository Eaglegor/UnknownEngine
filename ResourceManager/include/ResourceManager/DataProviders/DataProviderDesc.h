#pragma once

#include <string>
#include <ResourceManager/DataProviders/DataProviderType.h>
#include <Properties/Properties.h>
#include <DescriptorContainer.h>
#include <boost/variant.hpp>

namespace UnknownEngine
{
	namespace Core
	{
		struct DataProviderDesc
		{
			std::string name;
			DataProviderType type;
			boost::variant<Core::DescriptorContainer, Core::Properties> descriptor;
		};

	}
}
