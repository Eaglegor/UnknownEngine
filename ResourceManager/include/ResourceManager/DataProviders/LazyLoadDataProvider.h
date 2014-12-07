#pragma once
#include <ResourceManager/DataProviders/ReferencesCountingDataProvider.h>
#include <ResourceManager_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		class LazyLoadDataProvider : public ReferencesCountingDataProvider
		{
		public:
			RESOURCEMANAGER_EXPORT
			LazyLoadDataProvider ( const std::string& name );

			RESOURCEMANAGER_EXPORT
			virtual ~LazyLoadDataProvider();
			
			RESOURCEMANAGER_EXPORT
			virtual void startLoading() override{};
			
		protected:
			RESOURCEMANAGER_EXPORT
			virtual const ResourceContainer& internalGetResource();
			
		};
	}
}