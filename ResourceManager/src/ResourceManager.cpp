#include <stdafx.h>

#include <ResourceManager.h>
#include <DataProvider/IDataProviderFactory.h>
#include <DataProvider/DataProviderDesc.h>
#include <DataProvider/IDataProvider.h>
#include <ThreadPool.h>

#define ENABLE_CORE_SUBSYSTEM_INFO_LOG
#include <CoreLogging.h>

namespace UnknownEngine {
	namespace Core {

		template<>
		ResourceManager* Singleton<ResourceManager>::instance = nullptr;

		ResourceManager::ResourceManager() :
			internal_dictionary("ResourceManager.Dictionary", NUMERIC_IDENTIFIER_INITIAL_VALUE, INVALID_NUMERIC_IDENTIFIER),
			thread_pool(ThreadPool::createInstance(2))
		{
		}

		ResourceManager::~ResourceManager()
		{
			ThreadPool::destroyInstance();
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

		Loader::IDataProvider *ResourceManager::createDataProvider(const Loader::DataProviderDesc &desc) 
		{
			for( auto &factory : data_provider_factories )
			{
				if(factory.second->supportsType(desc.type))
				{	
					Loader::IDataProvider* data_provider = factory.second->createObject(desc);
					data_providers.push_back(data_provider);
					return data_provider;
				}
			}
			throw NoSuitableFactoryFoundException("Can't find factory to create data provider '" + desc.name + "'" );
		}
		
		bool ResourceManager::removeDataProvider ( Loader::IDataProvider* data_provider )
		{
			if(data_provider == nullptr) return true;
			if(!data_provider->mayBeDestructed()) return false;
			
			for( auto &factory : data_provider_factories )
			{
				if(factory.second->supportsType(data_provider->getType()))
				{	
					CORE_SUBSYSTEM_INFO ( "Destroying data provider  '" + data_provider->getName() + "'" );
					auto iter = std::find ( data_providers.begin(), data_providers.end(), data_provider );
					if ( iter != data_providers.end() ) *iter = nullptr;
					factory.second->destroyObject(data_provider);
					
					return true;
				}
			}
			
			return false;
		}

		
		void ResourceManager::cleanup()
		{
			for(size_t i = 0; i < data_providers.size(); ++i)
			{
				removeDataProvider(data_providers[i]);
			}
		}

	} // namespace Core
} // namespace UnknownEngine
