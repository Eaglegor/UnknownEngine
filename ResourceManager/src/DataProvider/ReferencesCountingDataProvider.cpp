#include <stdafx.h>

#include <ResourceManager/DataProviders/ReferencesCountingDataProvider.h>

namespace UnknownEngine
{
	namespace Core
	{

		ReferencesCountingDataProvider::ReferencesCountingDataProvider ( const char* name ):
		load_started ( false ),
		load_finished ( false ),
		name(name)
		{
		}

		const ResourceContainer& ReferencesCountingDataProvider::getResource()
		{
			return internalGetResource();
		}

		void ReferencesCountingDataProvider::waitUntilLoadFinished()
		{
			std::unique_lock<std::mutex> lock ( loading_finished_mutex );
			if(!load_started) return;
			while ( !load_finished )
			{
				wait_for_finish_var.wait ( lock );
			}
		}

		void ReferencesCountingDataProvider::onLoadFinished()
		{
			std::lock_guard<std::mutex> guard ( loading_finished_mutex );
			load_finished = true;

			wait_for_finish_var.notify_all();
		}

		void ReferencesCountingDataProvider::onLoadStarted()
		{
			std::lock_guard<std::mutex> guard(loading_started_mutex);
			load_started = true;
		}

		bool ReferencesCountingDataProvider::isLoadFinished()
		{
			std::lock_guard<std::mutex> guard ( loading_finished_mutex );
			return load_finished;
		}

		bool ReferencesCountingDataProvider::isLoadStarted()
		{
			std::lock_guard<std::mutex> guard(loading_started_mutex);
			return load_started;
		}

		const char* ReferencesCountingDataProvider::getName() const
		{
			return name.c_str();
		}
		
		ReferencesCountingDataProvider::~ReferencesCountingDataProvider()
		{
			waitUntilLoadFinished();
			internalUnload(resource_container);
		}

	} // namespace Loader
} // namespace UnknownEngine
