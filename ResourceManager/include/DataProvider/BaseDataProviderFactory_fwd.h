#pragma once

#include <DataProvider/DataProviderType.h>

namespace UnknownEngine
{
	namespace Core
	{
		template <typename ObjectType, typename ObjectTypeId, typename DescriptorClass>
		class BaseObjectFactory;
	}
	
	namespace Loader
	{
		class IDataProvider;
		struct DataProviderDesc;
		
		typedef Core::BaseObjectFactory<IDataProvider, DataProviderType, DataProviderDesc> BaseDataProviderFactory;
	}
}