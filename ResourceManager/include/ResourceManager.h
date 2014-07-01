#pragma once

#include <list>
#include <DataProvider/DataProviderType.h>

namespace UnknownEngine {

  namespace Loader
  {
    class IDataProviderFactory;
    class IDataProvider;
  }

  namespace Core {

    class Properties;

    class ResourceManager
    {
      public:
	ResourceManager();

	void addDataProviderFactory(Loader::IDataProviderFactory * factory);
	Loader::IDataProvider* getDataProvider(const Loader::DataProviderType &provider_type, const Properties& settings);

      private:
	std::list<Loader::IDataProviderFactory*> dataProviderFactories;

    };

  } // namespace Core
} // namespace UnknownEngine
