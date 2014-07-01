#pragma once

#include <boost/thread.hpp>
#include <memory>

#include <DataProvider/ReferencesCountingDataProvider.h>
#include <ResourceContainer.h>

namespace UnknownEngine {
	namespace Loader {

		class SeparateLoaderThreadDataProvider : public ReferencesCountingDataProvider
		{
			public:
				SeparateLoaderThreadDataProvider();
				~SeparateLoaderThreadDataProvider();

				void startLoading();
				const ResourceContainer& getResource();

			protected:
				virtual void internalLoad(ResourceContainer &out_container) = 0;

			private:
				void notifyLoadFinished();
				void notifyLoadStarted();
				bool loadingIsStarted();
				void separateLoaderThreadFunc();
				void waitUntilLoadFinished();

				std::unique_ptr<boost::thread> separate_loading_thread;
				boost::mutex loading_started_mutex;
				boost::mutex loading_finished_mutex;
				boost::condition_variable wait_for_finish_var;

				volatile bool load_finished;
				volatile bool load_started;
				ResourceContainer resource_container;
		};

	} // namespace Loader
} // namespace UnknownEngine
