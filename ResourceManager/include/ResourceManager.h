#pragma once

#include <unordered_map>
#include <DataProvider/DataProviderType.h>
#include <Exception.h>
#include <NumericIdentifierType.h>
#include <Singleton.h>
#include <Dictionary.h>
#include <NoSuitableFactoryFoundException.h>

namespace UnknownEngine {

	namespace Loader
	{
		class IDataProviderFactory;
		class IDataProvider;
		class DataProviderDesc;
	}

	namespace Core {

		class Properties;

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
				ResourceManager();
				virtual ~ResourceManager(){}

				/**
				 * @brief Registers new data provider factory
				 * @param factory - Factory to register
				 */
				void addDataProviderFactory(Loader::IDataProviderFactory * factory);

				/**
				 * @brief Unregisters the data provider factory
				 * @param factory - Factory to register
				 */
				void removeDataProviderFactory(Loader::IDataProviderFactory * factory);

				/**
				 * @brief Creates the data provider according to the passed descriptor
				 * @param desc - Descriptor of data provider to create
				 * @return Pointer to the created data provider
				 */
				Loader::IDataProvider* createDataProvider(const Loader::DataProviderDesc &desc) throw (NoSuitableFactoryFoundException);

			private:
				/// Registered data provider factories
				std::unordered_map<NumericIdentifierType, Loader::IDataProviderFactory*> data_provider_factories;

				/// Internal dictionary implementation
				Utils::Dictionary<NumericIdentifierType, std::string> internal_dictionary;
		};

	} // namespace Core
} // namespace UnknownEngine
