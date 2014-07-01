#pragma once

#include <DataProvider/ReferencesCountingDataProvider.h>
#include <ResourceContainer.h>

namespace UnknownEngine {
  namespace Loader {

    class SeparateLoaderThreadDataProvider : public ReferencesCountingDataProvider
    {
      public:
	SeparateLoaderThreadDataProvider();

	void startLoading();
	const ResourceContainer& getResource() const;

      protected:
	virtual void internalLoad(ResourceContainer &out_container) = 0;
	void notifyLoadFinished();
	void notifyLoadStarted();

      private:
	void separateLoaderThread();
	void waitUntilLoadFinished() const;

	volatile bool load_finished;
	volatile bool load_started;
	ResourceContainer resource_container;
    };

  } // namespace Loader
} // namespace UnknownEngine
