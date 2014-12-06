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

		class ReferencesCountingDataProvider : public IDataProvider
		{
			public:
				RESOURCEMANAGER_EXPORT
				ReferencesCountingDataProvider ( const std::string &name );

				virtual ~ReferencesCountingDataProvider();
				
				RESOURCEMANAGER_EXPORT
				virtual const ResourceContainer& getResource() override;

				RESOURCEMANAGER_EXPORT
				virtual void reserve() override;
				
				RESOURCEMANAGER_EXPORT
				virtual void release() override;

				RESOURCEMANAGER_EXPORT
				virtual bool mayBeDestructed() const override;

			protected:
				void onLoadStarted();
				void onLoadFinished();		
				
				bool isLoadStarted();
				bool isLoadFinished();
				
				virtual const ResourceContainer& internalGetResource() = 0;	

				void waitUntilLoadFinished();
				
				virtual void internalLoad ( ResourceContainer &out_container ) = 0;
				virtual void internalUnload ( ResourceContainer &container ){};

				ResourceContainer resource_container;
				
			private:
				void increaseReferencesCounter();

				void decreaseReferencesCounter();
				
				volatile bool load_started;
				volatile bool load_finished;
				
				std::mutex loading_started_mutex;
				std::mutex loading_finished_mutex;
				std::condition_variable wait_for_finish_var;
				
				volatile std::atomic<size_t> references_counter;

		};

	} // namespace Loader
} // namespace UnknownEngine
