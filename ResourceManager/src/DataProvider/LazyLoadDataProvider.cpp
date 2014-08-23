#include <stdafx.h>

#include <DataProvider/LazyLoadDataProvider.h>

namespace UnknownEngine
{
	namespace Loader
	{
		
		LazyLoadDataProvider::LazyLoadDataProvider ( const std::string& name ) : ReferencesCountingDataProvider ( name )
		{
		}
		
		LazyLoadDataProvider::~LazyLoadDataProvider()
		{
		}
		
		const ResourceContainer& LazyLoadDataProvider::internalGetResource()
		{
			if ( !isLoadStarted() )
			{
				onLoadStarted();
				internalLoad ( resource_container );
				onLoadFinished();
			}
			else
			{
				waitUntilLoadFinished();
			}
			return resource_container;
		}
	}
}