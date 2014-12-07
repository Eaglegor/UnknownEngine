#include <stdafx.h>

#include <ResourceManager/ResourceManager.h>
#include <ResourceManager/DataProviders/IDataProviderFactory.h>
#include <ResourceManager/DataProviders/DataProviderDesc.h>
#include <ResourceManager/DataProviders/IDataProvider.h>
#include <ResourceManager/ThreadPool.h>

#include <Logging.h>
#include <EngineLogLevel.h>

namespace UnknownEngine {
	namespace Core {

		template<>
		ResourceManager* Singleton<ResourceManager>::instance = nullptr;

		ResourceManager::ResourceManager():
		thread_pool(ThreadPool::createInstance(2)),
		logger("Core.ResourceManager", ENGINE_LOG_LEVEL)
		{
		}

		ResourceManager::~ResourceManager()
		{
			//internalCleanup(true);
			ThreadPool::destroyInstance();
		}
		
		void ResourceManager::addDataProviderFactory(IDataProviderFactory * factory)
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			auto iter = data_provider_factories.find(factory->getName());
			if(iter != data_provider_factories.end())
			{
				LOG_ERROR(logger, "Failed to register data provider factory " + factory->getName() +". Factory with the same name already registered" );
				return;
			}
			data_provider_factories.emplace(factory->getName(), factory);
		}

		void ResourceManager::removeDataProviderFactory(IDataProviderFactory * factory)
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			auto iter = data_provider_factories.find(factory->getName());
			if(iter == data_provider_factories.end())
			{
				LOG_ERROR(logger, "Failed to unregister data provider factory " + factory->getName() + ". Factory not registered");
			}
			data_provider_factories.erase(iter);
		}	

		IDataProvider *ResourceManager::createDataProvider(const DataProviderDesc &desc) 
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			for( auto &factory : data_provider_factories )
			{
				if(factory.second->supportsType(desc.type))
				{	
					IDataProvider* data_provider = factory.second->createObject(desc);
					if(!data_provider)
					{
						LOG_ERROR(logger, "Failed to create data provider " + desc.name);
						return nullptr;
					}
					data_providers.emplace(desc.name, data_provider);
					return data_provider;
				}
			}
			LOG_ERROR(logger, "No suitable data provider factory found to create data provider " + desc.name);
			return nullptr;
		}
		
		void ResourceManager::removeDataProvider ( IDataProvider* data_provider )
		{
			std::lock_guard<LockPrimitive> guard(mutex);
			if(data_provider == nullptr) 
			{
				LOG_ERROR(logger, "Nullptr passed as data provider to be destroyed. Nothing is to be done.");
				return;
			}
			
			if(!data_provider->mayBeDestructed()) 
			{
				LOG_DEBUG(logger, "Data provider " + data_provider->getName() + " is still in use and can't be destroyed" );
				return;
			}
			
			for( auto &factory : data_provider_factories )
			{
				if(factory.second->supportsType(data_provider->getType()))
				{	
					LOG_INFO(logger, "Destroying data provider  '" + data_provider->getName() + "'" );
					data_providers.erase(data_provider->getName());
					factory.second->destroyObject(data_provider);
					LOG_INFO(logger, "Data provider  '" + data_provider->getName() + "' destroyed");
					return;
				}
			}
			LOG_ERROR(logger, "No suitable data provider factory found to destroy data provider " + data_provider->getName());
			
		}

		void ResourceManager::cleanup()
		{
			internalCleanup(false);
		}
		
		void ResourceManager::internalCleanup(bool force_destruction)
		{
			std::vector<std::string> removed_data_providers;
			
			std::lock_guard<LockPrimitive> guard(mutex);
			
			for(auto &iter : data_providers)
			{
				if(/*!force_destruction &&*/ !iter.second->mayBeDestructed())
				{
					LOG_DEBUG(logger, "Data provider " + iter.second->getName() + " is still in use and can't be destroyed" );
					continue;
				}
				
				if(!iter.second->mayBeDestructed())
				{
					LOG_WARNING(logger, "Destroying the in-use data provider " + iter.second->getName() + " because of forced cleanup" );
				}

				bool success = false;
				for( auto &factory : data_provider_factories )
				{
					if(factory.second->supportsType(iter.second->getType()))
					{	
						LOG_INFO(logger, "Destroying data provider  '" + iter.second->getName() + "'" );
						removed_data_providers.push_back(iter.second->getName());
						std::string name = iter.second->getName();
						factory.second->destroyObject(iter.second);
						LOG_INFO(logger, "Data provider " + name + " destroyed");
						success = true;
						break;
					}
				}
				if(!success)
				{
					LOG_ERROR(logger, "No suitable data provider factory found to destroy data provider " + iter.second->getName());
				}
			}
			
			for(const std::string& name : removed_data_providers)
			{
				data_providers.erase(name);
			}
		}

	} // namespace Core
} // namespace UnknownEngine
