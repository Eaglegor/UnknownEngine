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

    bool ReferencesCountingDataProvider::mayBeDestructed() const
    {
      return this->references_counter == 0;
    }

    void ReferencesCountingDataProvider::increaseReferencesCounter()
    {
      ++this->references_counter; // ATOMIC!
    }

    void ReferencesCountingDataProvider::decreaseReferencesCounter()
    {
      ++this->references_counter; // ATOMIC!
    }

  } // namespace Loader
} // namespace UnknownEngine
