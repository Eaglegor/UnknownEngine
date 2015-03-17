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
			waitUntilAllDataProvidersReleased();
			ThreadPool::destroyInstance();
		}
		
		void ResourceManager::addDataProviderFactory(IDataProviderFactory * factory)
		{
			std::lock_guard<LockPrimitive> guard(factories_mutex);
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
			std::lock_guard<LockPrimitive> guard(factories_mutex);
			auto iter = data_provider_factories.find(factory->getName());
			if(iter == data_provider_factories.end())
			{
				LOG_ERROR(logger, "Failed to unregister data provider factory " + factory->getName() + ". Factory not registered");
			}
			data_provider_factories.erase(iter);
		}	

		IDataProvider *ResourceManager::createDataProvider(const DataProviderDesc &desc) 
		{
			std::lock_guard<LockPrimitive> guard(factories_mutex);
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
					DataProviderWrapper wrapper;
					wrapper.factory_name = factory.second->getName();
					wrapper.data_provider = data_provider;
					{
						std::lock_guard<LockPrimitive> guard(data_providers_mutex);
						data_providers.emplace(desc.name, wrapper);
					}
					return data_provider;
				}
			}
			LOG_ERROR(logger, "No suitable data provider factory found to create data provider " + desc.name);
			return nullptr;
		}

		IDataProvider* ResourceManager::getDataProvider ( const char* name )
		{
			std::lock_guard<LockPrimitive> guard(data_providers_mutex);
			
			auto iter = data_providers.find(name);
			if(iter == data_providers.end()) return nullptr;
			
			++iter->second.ref_counter;
			return iter->second.data_provider;
		}
		
		void ResourceManager::releaseDataProvider ( IDataProvider* data_provider )
		{
			if(data_provider == nullptr) 
			{
				LOG_WARNING(logger, "Trying to release nullptr data provider. Nothing is to be done.");
				return;
			}

			std::unique_lock<LockPrimitive> dp_guard(data_providers_mutex);
			auto iter = data_providers.find(data_provider->getName());
			if(iter == data_providers.end()) 
			{
				LOG_ERROR(logger, "Trying to release unknown data provider " + data_provider->getName() + ". Check if it was created correctly.");
				return;
			}
			
			DataProviderWrapper& wrapper = iter->second;
			
			if(--wrapper.ref_counter > 0)
			{
				return;
			}
			
			std::string data_provider_name = data_provider->getName();
			dp_guard.unlock();
			
			std::unique_lock<LockPrimitive> factory_guard(factories_mutex);
			
			auto factory_iter = data_provider_factories.find(wrapper.factory_name);
			if(factory_iter == data_provider_factories.end())
			{
				LOG_ERROR(logger, "Factory " + wrapper.factory_name + "needed to destroy data provider " + wrapper.data_provider->getName() + " not found. Was it's plugin already unloaded?");
				return;
			}
			IDataProviderFactory* factory = factory_iter->second;
			
			factory_guard.unlock();
			
			factory->destroyObject(wrapper.data_provider);
			
			dp_guard.lock();
			data_providers.erase(data_provider_name);
			cv.notify_all();
			dp_guard.unlock();

		}

		void ResourceManager::waitUntilAllDataProvidersReleased()
		{
			std::unique_lock<LockPrimitive> guard(data_providers_mutex);
			const std::chrono::seconds RELEASE_WARNING_TIMEOUT(1);
			while(!data_providers.empty())
			{
				LOG_INFO(logger, "Waiting until all data providers are released. Remaining unreleased data providers: " + std::to_string(data_providers.size()));
				std::cv_status status = cv.wait_for(guard, RELEASE_WARNING_TIMEOUT);
				if(status == std::cv_status::timeout)
				{
					LOG_WARNING(logger, "Still waiting for release of data providers. Please check if some component or data provider hasn't released it's data.");
					LOG_WARNING(logger, "Unreleased data providers list:");
					for(auto &iter : data_providers)
					{
						LOG_WARNING(logger, iter.second.data_provider->getName());
					}
				}
			}
		}
		
	} // namespace Core
} // namespace UnknownEngine
