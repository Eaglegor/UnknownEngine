#pragma once

#include <DataProvider/IDataProvider.h>

namespace UnknownEngine {
  namespace Loader {

    class ReferencesCountingDataProvider : public IDataProvider
    {
      public:
        ReferencesCountingDataProvider();

        virtual const ResourceContainer& getResource() const = 0;
        virtual void release();
        virtual bool mayBeDestructed() const;

      protected:
        void increaseReferencesCounter();
        void decreaseReferencesCounter();

      private:
        volatile size_t references_counter;

    };

  } // namespace Loader
} // namespace UnknownEngine
