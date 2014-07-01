#include <stdafx.h>

#include <DataProvider/SeparateLoaderThreadDataProvider.h>

namespace UnknownEngine {
  namespace Loader {

    SeparateLoaderThreadDataProvider::SeparateLoaderThreadDataProvider() : load_started(false), load_finished(false)
    {
    }

    void SeparateLoaderThreadDataProvider::startLoading()
    {
      separateLoaderThread(); // To separate thread
    }

    const ResourceContainer &SeparateLoaderThreadDataProvider::getResource() const
    {
      waitUntilLoadFinished();
      return resource_container;
    }

    void SeparateLoaderThreadDataProvider::notifyLoadFinished()
    {
      this->load_finished = true;
    }

    void SeparateLoaderThreadDataProvider::notifyLoadStarted()
    {
      this->load_started = true;
    }

    void SeparateLoaderThreadDataProvider::separateLoaderThread()
    {
      notifyLoadStarted();
      this->internalLoad(resource_container);
      notifyLoadFinished();
    }

    void SeparateLoaderThreadDataProvider::waitUntilLoadFinished() const
    {
      while(!load_finished);
    }

  } // namespace Loader
} // namespace UnknownEngine
