#pragma once

#include <boost/thread.hpp>
#include <memory>

#include <DataProvider/ReferencesCountingDataProvider.h>
#include <ResourceContainer.h>

namespace UnknownEngine {
	namespace Loader {

		/// Data provider implementation loading resources in the separate thread
		class SeparateLoaderThreadDataProvider : public ReferencesCountingDataProvider
		{
			public:
				SeparateLoaderThreadDataProvider(const std::string &name);
				~SeparateLoaderThreadDataProvider();

				/// Starts the loading thread
				void startLoading();

				/// Waits for loader thread to be finished and returns the data loaded
				const ResourceContainer& getResource();

			protected:
				/// Worker method
				virtual void internalLoad(ResourceContainer &out_container) = 0;

			private:

				/// Worker method starter
				void separateLoaderThreadFunc();

				/// Waits until loading is finished
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
