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
		struct DataProviderDesc;
		
		typedef Core::AbstractObjectFactory<IDataProvider, DataProviderType, DataProviderDesc> IDataProviderFactory;
	}
}