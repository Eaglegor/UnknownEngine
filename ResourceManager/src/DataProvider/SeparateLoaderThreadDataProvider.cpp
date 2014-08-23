#include <stdafx.h>

#include <DataProvider/SeparateLoaderThreadDataProvider.h>

namespace UnknownEngine {
	namespace Loader {

		SeparateLoaderThreadDataProvider::SeparateLoaderThreadDataProvider(const std::string &name) :
			ReferencesCountingDataProvider(name),
			separate_loading_thread(nullptr)
		{
		}

		SeparateLoaderThreadDataProvider::~SeparateLoaderThreadDataProvider()
		{
		}

		void SeparateLoaderThreadDataProvider::startLoading()
		{
			if(isLoadStarted()) return;
			onLoadStarted();
			separate_loading_thread = std::move(std::unique_ptr<boost::thread>(new boost::thread(boost::bind(&SeparateLoaderThreadDataProvider::separateLoaderThreadFunc, this))));
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
