#include <stdafx.h>

#include <DataProvider/ReferencesCountingDataProvider.h>

namespace UnknownEngine {
	namespace Loader {

		ReferencesCountingDataProvider::ReferencesCountingDataProvider(const std::string &name)
			: references_counter(1),
			  IDataProvider(name)
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
			return references_counter == 0;
		}

		void ReferencesCountingDataProvider::increaseReferencesCounter()
		{
			references_counter.fetch_add(1);
		}

		void ReferencesCountingDataProvider::decreaseReferencesCounter()
		{
			references_counter.fetch_sub(1);
		}

		const ResourceContainer& ReferencesCountingDataProvider::getResource()
		{
			if(!loading_finished)
			{
				internalLoad(resource_container);
				loading_finished = true;
			}
			return resource_container;
		}
		
	} // namespace Loader
} // namespace UnknownEngine
