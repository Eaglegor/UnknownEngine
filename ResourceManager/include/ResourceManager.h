#pragma once

#include <ResourceManager_export.h>
#include <unordered_map>
#include <DataProvider/DataProviderType.h>
#include <Exception.h>
#include <NumericIdentifierType.h>
#include <Singleton.h>
#include <Dictionary.h>
#include <NoSuitableFactoryFoundException.h>
#include <Properties/Properties_fwd.h>
#include <DataProvider/IDataProviderFactory_fwd.h>

namespace UnknownEngine {

	namespace Loader
	{
		class IDataProvider;
		struct DataProviderDesc;
	}

	namespace Core {

		class ILogger;

		class ThreadPool;

		class ResourceManager : public Singleton<ResourceManager>
		{
			public:
				RESOURCEMANAGER_EXPORT
				ResourceManager();

				virtual ~ResourceManager();

				RESOURCEMANAGER_EXPORT
				void addDataProviderFactory(Loader::IDataProviderFactory * factory);

				RESOURCEMANAGER_EXPORT
				void removeDataProviderFactory(Loader::IDataProviderFactory * factory);

				RESOURCEMANAGER_EXPORT
				Loader::IDataProvider* createDataProvider(const Loader::DataProviderDesc &desc) ;

				RESOURCEMANAGER_EXPORT
				bool removeDataProvider(Loader::IDataProvider* data_provider);
				
				RESOURCEMANAGER_EXPORT
				void cleanup();
								
			private:
				std::unordered_map<NumericIdentifierType, Loader::IDataProviderFactory*> data_provider_factories;
				
				std::vector<Loader::IDataProvider*> data_providers;

				Utils::Dictionary<NumericIdentifierType, std::string> internal_dictionary;
				
				ThreadPool* thread_pool;
				
				ILogger* logger;
		};

#ifdef _MSC_VER
#ifndef ResourceManager_EXPORTS
		extern template class RESOURCEMANAGER_EXPORT Singleton<ResourceManager>;
#else
		template class RESOURCEMANAGER_EXPORT Singleton<ResourceManager>;
#endif
#endif

	} // namespace Core
} // namespace UnknownEngine
