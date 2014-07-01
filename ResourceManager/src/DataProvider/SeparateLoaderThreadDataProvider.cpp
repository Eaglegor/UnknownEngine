#include <stdafx.h>

#include <DataProvider/SeparateLoaderThreadDataProvider.h>

namespace UnknownEngine {
	namespace Loader {

		SeparateLoaderThreadDataProvider::SeparateLoaderThreadDataProvider() :
			load_started(false),
			load_finished(false),
			separate_loading_thread(nullptr)
		{
		}

		SeparateLoaderThreadDataProvider::~SeparateLoaderThreadDataProvider()
		{
		}

		void SeparateLoaderThreadDataProvider::startLoading()
		{
			boost::lock_guard<boost::mutex> guard(loading_started_mutex);
			if(load_started) return;
			separate_loading_thread = std::move(std::unique_ptr<boost::thread>(new boost::thread(boost::bind(&SeparateLoaderThreadDataProvider::separateLoaderThreadFunc, this))));
			load_started = true;
		}

		const ResourceContainer &SeparateLoaderThreadDataProvider::getResource()
		{
			increaseReferencesCounter();
			waitUntilLoadFinished();
			return resource_container;
		}

		void SeparateLoaderThreadDataProvider::separateLoaderThreadFunc()
		{
			internalLoad(resource_container);

			{
				boost::lock_guard<boost::mutex> guard(loading_finished_mutex);
				load_finished = true;
			}

			wait_for_finish_var.notify_all();
		}

		void SeparateLoaderThreadDataProvider::waitUntilLoadFinished()
		{
			boost::unique_lock<boost::mutex> lock(loading_finished_mutex);
			while(!load_finished)
			{
				wait_for_finish_var.wait(lock);
			}
		}

	} // namespace Loader
} // namespace UnknownEngine
