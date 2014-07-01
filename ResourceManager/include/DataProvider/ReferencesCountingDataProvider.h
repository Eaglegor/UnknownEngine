#pragma once

#include <atomic>
#include <DataProvider/IDataProvider.h>

namespace UnknownEngine {
  namespace Loader {

    class ReferencesCountingDataProvider : public IDataProvider
    {
      public:
        ReferencesCountingDataProvider();

        virtual const ResourceContainer& getResource() const = 0;
        virtual void release();
		virtual bool mayBeDestructed();

      protected:
        void increaseReferencesCounter();
        void decreaseReferencesCounter();

      private:
		volatile std::atomic<size_t> references_counter;

    };

  } // namespace Loader
} // namespace UnknownEngine
