#pragma once

#include <ResourceManager_export.h>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <DataProvider/IDataProvider.h>
#include <ResourceContainer.h>

namespace UnknownEngine
{
	namespace Loader
	{

		/// Implementation of data provider with references counter
		class ReferencesCountingDataProvider : public IDataProvider
		{
			public:
				RESOURCEMANAGER_EXPORT
				ReferencesCountingDataProvider ( const std::string &name );

				virtual ~ReferencesCountingDataProvider();
				
				/// Returns the loaded data
				RESOURCEMANAGER_EXPORT
				virtual const ResourceContainer& getResource() override;

				/// Increases references counter
				RESOURCEMANAGER_EXPORT
				virtual void reserve() override;
				
				/// Decreases references counter
				RESOURCEMANAGER_EXPORT
				virtual void release() override;

				/// Returns true if there are no references to this provider
				RESOURCEMANAGER_EXPORT
				virtual bool mayBeDestructed() const override;

			protected:
				void onLoadStarted();
				void onLoadFinished();		
				
				bool isLoadStarted();
				bool isLoadFinished();
				
				/// Actual resource getter
				virtual const ResourceContainer& internalGetResource() = 0;	

				/// Waits until loading is finished
				void waitUntilLoadFinished();
				
				virtual void internalLoad ( ResourceContainer &out_container ) = 0;

				ResourceContainer resource_container;
				
			private:
				/// Increases the references counter
				void increaseReferencesCounter();

				/// Decreases the references counter
				void decreaseReferencesCounter();
				
				volatile bool load_finished;
				volatile bool load_started;
				
				std::mutex loading_started_mutex;
				std::mutex loading_finished_mutex;
				std::condition_variable wait_for_finish_var;
				
				volatile std::atomic<size_t> references_counter; ///< References counter

		};

	} // namespace Loader
} // namespace UnknownEngine
