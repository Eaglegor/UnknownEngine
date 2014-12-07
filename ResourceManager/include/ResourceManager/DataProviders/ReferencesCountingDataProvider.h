#pragma once

#include <ResourceManager_export.h>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <ResourceManager/DataProviders/IDataProvider.h>
#include <ResourceManager/ResourceContainer.h>

namespace UnknownEngine
{
	namespace Core
	{

		class ReferencesCountingDataProvider : public IDataProvider
		{
			public:
				RESOURCEMANAGER_EXPORT
				ReferencesCountingDataProvider ( const char* name );

				virtual ~ReferencesCountingDataProvider();
				
				RESOURCEMANAGER_EXPORT
				virtual const ResourceContainer& getResource() override;

				RESOURCEMANAGER_EXPORT
				virtual void reserve() override;
				
				RESOURCEMANAGER_EXPORT
				virtual void release() override;

				RESOURCEMANAGER_EXPORT
				virtual bool mayBeDestructed() const override;

				RESOURCEMANAGER_EXPORT
				virtual const char* getName() const override;
				
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

				std::string name;
				
		};

	} // namespace Loader
} // namespace UnknownEngine
