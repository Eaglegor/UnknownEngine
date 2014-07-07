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

		class ResourceManager : public Singleton<ResourceManager>
		{
			public:
				ResourceManager();
				virtual ~ResourceManager(){}

				void addDataProviderFactory(Loader::IDataProviderFactory * factory);
				void removeDataProviderFactory(Loader::IDataProviderFactory * factory);

				Loader::IDataProvider* createDataProvider(const Loader::DataProviderDesc &desc) throw (NoSuitableFactoryFoundException);

			private:
				std::unordered_map<NumericIdentifierType, Loader::IDataProviderFactory*> data_provider_factories;
				Utils::Dictionary<NumericIdentifierType, std::string> internal_dictionary;
		};

	} // namespace Core
} // namespace UnknownEngine
