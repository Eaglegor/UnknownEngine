#pragma once

#include <atomic>
#include <DataProvider/IDataProvider.h>

namespace UnknownEngine {
  namespace Loader {

	/// Implementation of data provider with references counter
    class ReferencesCountingDataProvider : public IDataProvider
    {
      public:
        ReferencesCountingDataProvider();

		/// Returns the loaded data increasing the references counter
        virtual const ResourceContainer& getResource() const = 0;

		/// Decreases references counter
        virtual void release();

		/// Returns true if there are no references to this provider
		virtual bool mayBeDestructed();

      protected:
		/// Increases the references counter
        void increaseReferencesCounter();

		/// Decreases the references counter
        void decreaseReferencesCounter();

      private:
		volatile std::atomic<size_t> references_counter; ///< References counter

    };

  } // namespace Loader
} // namespace UnknownEngine