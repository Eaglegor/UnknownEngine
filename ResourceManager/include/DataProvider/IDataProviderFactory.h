#pragma once

#include <AbstractObjectFactory.h>
#include <DataProvider/DataProviderType.h>

namespace UnknownEngine {

	namespace Core
	{
		class Properties;
	}

	namespace Loader {

		class IDataProvider;
		class DataProviderDesc;

		class IDataProviderFactory : public Core::AbstractObjectFactory<IDataProvider, DataProviderType, DataProviderDesc>
		{
		};

	} // namespace Loader
} // namespace UnknownEngine
