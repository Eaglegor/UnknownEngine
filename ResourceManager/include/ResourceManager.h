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

		class ThreadPool;
		
		/**
		 * @brief Resource manager class
		 *
		 * ###Concept
		 * Resource manager is purposed to load/unload resources. It provides user code with access
		 * to the data providers that do the actual load/unload/store work.
		 *
		 * ###Usage
		 * When a user wants to load a resource it calls the createDataProvider() method of resource manager.
		 * Resource manager finds the factory suitable to create the specified data provider type and delegates the
		 * creation of data provider to it.
		 *
		 * When the plugin supporting data loading is loaded it creates the data provider factories and registers
		 * them with a call to addDataProviderFactory()
		 *
		 */
		class ResourceManager : public Singleton<ResourceManager>
		{
			public:
				RESOURCEMANAGER_EXPORT
				ResourceManager();

				virtual ~ResourceManager();

				/**
				 * @brief Registers new data provider factory
				 * @param factory - Factory to register
				 */
				RESOURCEMANAGER_EXPORT
				void addDataProviderFactory(Loader::IDataProviderFactory * factory);

				/**
				 * @brief Unregisters the data provider factory
				 * @param factory - Factory to register
				 */
				RESOURCEMANAGER_EXPORT
				void removeDataProviderFactory(Loader::IDataProviderFactory * factory);

				/**
				 * @brief Creates the data provider according to the passed descriptor
				 * @param desc - Descriptor of data provider to create
				 * @return Pointer to the created data provider
				 */
				RESOURCEMANAGER_EXPORT
				Loader::IDataProvider* createDataProvider(const Loader::DataProviderDesc &desc) ;

				/**
				 * @brief Removes specified data provider is it's allowed
				 * @param data_provider - Data provider to be removed
				 * @return True if data provider was removed. False otherwise (data provider may be used by someone else)
				 */
				RESOURCEMANAGER_EXPORT
				bool removeDataProvider(Loader::IDataProvider* data_provider);
				
				/**
				 * @brief Removes all data providers which may be removed
				 */
				RESOURCEMANAGER_EXPORT
				void cleanup();
								
			private:
				/// Registered data provider factories
				std::unordered_map<NumericIdentifierType, Loader::IDataProviderFactory*> data_provider_factories;
				
				std::vector<Loader::IDataProvider*> data_providers;

				/// Internal dictionary implementation
				Utils::Dictionary<NumericIdentifierType, std::string> internal_dictionary;
				
				/// Thread pool for data providers
				ThreadPool* thread_pool;
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
