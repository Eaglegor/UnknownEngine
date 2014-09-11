#include <stdafx.h>

#include <DataProvider/SeparateLoaderThreadDataProvider.h>
#include <ThreadPool.h>

namespace UnknownEngine {
	namespace Loader {

		SeparateLoaderThreadDataProvider::SeparateLoaderThreadDataProvider(const std::string &name) :
			ReferencesCountingDataProvider(name)
		{
		}

		SeparateLoaderThreadDataProvider::~SeparateLoaderThreadDataProvider()
		{
		}

		void SeparateLoaderThreadDataProvider::startLoading()
		{
			if(isLoadStarted()) return;
			onLoadStarted();
			Core::ThreadPool::getSingleton()->pushTask( std::bind(&SeparateLoaderThreadDataProvider::separateLoaderThreadFunc, this) );
		}

		void SeparateLoaderThreadDataProvider::separateLoaderThreadFunc()
		{
			internalLoad(resource_container);
			
			onLoadFinished();
		}

		const ResourceContainer& SeparateLoaderThreadDataProvider::internalGetResource()
		{
			waitUntilLoadFinished();
			return resource_container;
		}
		
	} // namespace Loader
} // namespace UnknownEngine
