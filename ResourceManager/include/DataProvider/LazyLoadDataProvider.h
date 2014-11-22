#pragma once
#include <DataProvider/ReferencesCountingDataProvider.h>
#include <ResourceManager_export.h>

namespace UnknownEngine
{
	namespace Loader
	{
		class LazyLoadDataProvider : public Loader::ReferencesCountingDataProvider
		{
		public:
			RESOURCEMANAGER_EXPORT
			LazyLoadDataProvider ( const std::string& name );

			RESOURCEMANAGER_EXPORT
			virtual ~LazyLoadDataProvider();
			
			/// Does nothing. All loading is done in getResource()
			RESOURCEMANAGER_EXPORT
			virtual void startLoading() override{};
			
		protected:
			RESOURCEMANAGER_EXPORT
			virtual const ResourceContainer& internalGetResource();
			
		};
	}
}