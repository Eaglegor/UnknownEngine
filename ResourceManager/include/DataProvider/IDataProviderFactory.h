#pragma once

#include <AbstractObjectFactory.h>
#include <DataProvider/DataProviderType.h>
#include <Properties/Properties_fwd.h>

namespace UnknownEngine {

	namespace Loader {

		class IDataProvider;
		struct DataProviderDesc;

		/**
		 * @brief The factory of data providers
		 *
		 * There are no inbuilt data providers in the Unknown %Engine. All data loaders are created by the plugins.
		 * When a user wants to load a resource it calls the createDataProvider() method of resource manager.
		 * Resource manager finds the factory suitable to create the specified data provider type and delegates the
		 * creation of data provider to it.
		 *
		 */
		class IDataProviderFactory : public Core::AbstractObjectFactory<IDataProvider, DataProviderType, DataProviderDesc>
		{
		};

	} // namespace Loader
} // namespace UnknownEngine
