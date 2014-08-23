#include <stdafx.h>

#include <DataProvider/ReferencesCountingDataProvider.h>

namespace UnknownEngine
{
	namespace Loader
	{

		ReferencesCountingDataProvider::ReferencesCountingDataProvider ( const std::string &name )
			: references_counter ( 1 ),
			  load_started ( false ),
			  load_finished ( false ),
			  IDataProvider ( name )
		{
		}

		void ReferencesCountingDataProvider::reserve()
		{
			this->increaseReferencesCounter();
		}

		void ReferencesCountingDataProvider::release()
		{
			this->decreaseReferencesCounter();
		}

		bool ReferencesCountingDataProvider::mayBeDestructed() const
		{
			return ( references_counter == 0 ) && ( load_finished || !load_started );
		}

		void ReferencesCountingDataProvider::increaseReferencesCounter()
		{
			references_counter.fetch_add ( 1 );
		}

		void ReferencesCountingDataProvider::decreaseReferencesCounter()
		{
			references_counter.fetch_sub ( 1 );
		}

		const ResourceContainer& ReferencesCountingDataProvider::getResource()
		{
			return internalGetResource();
		}

		void ReferencesCountingDataProvider::waitUntilLoadFinished()
		{
			boost::unique_lock<boost::mutex> lock ( loading_finished_mutex );
			while ( !load_finished )
			{
				wait_for_finish_var.wait ( lock );
			}
		}

		void ReferencesCountingDataProvider::onLoadFinished()
		{
			boost::lock_guard<boost::mutex> guard ( loading_finished_mutex );
			load_finished = true;

			wait_for_finish_var.notify_all();
		}

		void ReferencesCountingDataProvider::onLoadStarted()
		{
			boost::lock_guard<boost::mutex> guard(loading_started_mutex);
			load_started = true;
		}

		bool ReferencesCountingDataProvider::isLoadFinished()
		{
			boost::lock_guard<boost::mutex> guard ( loading_finished_mutex );
			return load_finished;
		}

		bool ReferencesCountingDataProvider::isLoadStarted()
		{
			boost::lock_guard<boost::mutex> guard(loading_started_mutex);
			return load_started;
		}

		ReferencesCountingDataProvider::~ReferencesCountingDataProvider()
		{
		}

	} // namespace Loader
} // namespace UnknownEngine
