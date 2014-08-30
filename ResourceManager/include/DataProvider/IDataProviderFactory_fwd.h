#pragma once

#include <DataProvider/DataProviderType.h>

namespace UnknownEngine
{
	
	namespace Core
	{
		template <typename ObjectType, typename ObjectTypeId, typename DescriptorClass>
		class AbstractObjectFactory;
	}
	
	namespace Loader
	{
		class IDataProvider;
		class DataProviderDesc;
		
		/**
		 * @brief The factory of data providers
		 *
		 * There are no inbuilt data providers in the Unknown %Engine. All data loaders are created by the plugins.
		 * When a user wants to load a resource it calls the createDataProvider() method of resource manager.
		 * Resource manager finds the factory suitable to create the specified data provider type and delegates the
		 * creation of data provider to it.
		 *
		 */
		typedef Core::AbstractObjectFactory<IDataProvider, DataProviderType, DataProviderDesc> IDataProviderFactory;
	}
}