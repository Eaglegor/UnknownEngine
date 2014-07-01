#include <stdafx.h>

#include <DataProvider/ReferencesCountingDataProvider.h>

namespace UnknownEngine {
	namespace Loader {

		ReferencesCountingDataProvider::ReferencesCountingDataProvider() : references_counter(1)
		{
		}

		void UnknownEngine::Loader::ReferencesCountingDataProvider::release()
		{
			this->decreaseReferencesCounter();
		}

		bool ReferencesCountingDataProvider::mayBeDestructed()
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

	} // namespace Loader
} // namespace UnknownEngine
