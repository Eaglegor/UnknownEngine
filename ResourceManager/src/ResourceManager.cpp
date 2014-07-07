#include <stdafx.h>

#include <ResourceManager.h>
#include <DataProvider/IDataProviderFactory.h>
#include <DataProvider/DataProviderDesc.h>

namespace UnknownEngine {
	namespace Core {

		template<>
		ResourceManager* Singleton<ResourceManager>::instance = nullptr;

		ResourceManager::ResourceManager() :
			internal_dictionary(NUMERIC_IDENTIFIER_INITIAL_VALUE, INVALID_NUMERIC_IDENTIFIER)
		{
		}

		void ResourceManager::addDataProviderFactory(Loader::IDataProviderFactory * factory)
		{
			if(factory->getInternalId() != Core::INVALID_NUMERIC_IDENTIFIER) return;
			NumericIdentifierType new_id = internal_dictionary.registerNewValue(factory->getName());
			factory->setInternalId(new_id);
			data_provider_factories[new_id] = factory;
		}

		void ResourceManager::removeDataProviderFactory(Loader::IDataProviderFactory * factory)
		{
			if(factory->getInternalId() == Core::INVALID_NUMERIC_IDENTIFIER) return;
			data_provider_factories.erase(factory->getInternalId());
			factory->setInternalId(Core::INVALID_NUMERIC_IDENTIFIER);
		}

		Loader::IDataProvider *ResourceManager::createDataProvider(const Loader::DataProviderDesc &desc) throw (NoSuitableFactoryFoundException)
		{
			for( auto &factory : data_provider_factories )
			{
				if(factory.second->supportsType(desc.type)) return factory.second->createObject(desc);
			}
			throw NoSuitableFactoryFoundException("Can't find factory to create data provider");
		}

	} // namespace Core
} // namespace UnknownEngine
