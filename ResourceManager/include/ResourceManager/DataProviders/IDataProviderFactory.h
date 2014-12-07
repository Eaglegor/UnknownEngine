#pragma once
#include <ResourceManager_export.h>
#include <ResourceManager/DataProviders/DataProviderType.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct DataProviderDesc;
		class IDataProvider;
		
		class IDataProviderFactory
		{
			public:
				RESOURCEMANAGER_EXPORT
				virtual ~IDataProviderFactory(){}

				RESOURCEMANAGER_EXPORT
				virtual const char* getName() const = 0;

				RESOURCEMANAGER_EXPORT
				virtual bool supportsType ( const DataProviderType &object_type ) const = 0;

				RESOURCEMANAGER_EXPORT
				virtual IDataProvider* createObject ( const DataProviderDesc& desc ) = 0;

				RESOURCEMANAGER_EXPORT
				virtual void destroyObject ( IDataProvider* object ) = 0;
		};

	} // namespace Core
} // namespace UnknownEngine
