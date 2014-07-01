#pragma once

#include <unordered_set>
#include <DataProvider/DataProviderType.h>

namespace UnknownEngine {

    namespace Core
    {
        class Properties;
    }

    namespace Loader {

        class IDataProvider;

        class IDataProviderFactory
        {
        public:
	    virtual const std::unordered_set<DataProviderType>& getSupportedDataProvidersSet() = 0;
	    virtual bool canCreateDataProvider(const DataProviderType &provider_type) = 0;
	    virtual Loader::IDataProvider* getDataProvider(const DataProviderType& provider_type, const Core::Properties& settings) = 0;
        };

    } // namespace Loader
} // namespace UnknownEngine
