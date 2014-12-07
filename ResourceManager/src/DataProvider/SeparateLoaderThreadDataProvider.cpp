#include <stdafx.h>

#include <ResourceManager/DataProviders/SeparateLoaderThreadDataProvider.h>
#include <ResourceManager/ThreadPool.h>

namespace UnknownEngine {
	namespace Core {

		SeparateLoaderThreadDataProvider::SeparateLoaderThreadDataProvider(const std::string &name) :
			ReferencesCountingDataProvider(name.c_str())
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
