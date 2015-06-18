#pragma once

#include <ResourceManager_export.h>
#include <unordered_map>
#include <Singleton.h>
#include <LogHelper.h>
#include <mutex>
#include <condition_variable>

namespace UnknownEngine
{
	namespace Core
	{

		class IDataProvider;
		struct DataProviderDesc;
		class ThreadPool;
		class IDataProviderFactory;

		class ResourceManager : public Singleton<ResourceManager>
		{
			public:
				ResourceManager();
				virtual ~ResourceManager();

				RESOURCEMANAGER_EXPORT
				void addDataProviderFactory ( IDataProviderFactory * factory );

				RESOURCEMANAGER_EXPORT
				void removeDataProviderFactory ( IDataProviderFactory * factory );

				RESOURCEMANAGER_EXPORT
				IDataProvider* createDataProvider ( const DataProviderDesc &desc ) ;

				RESOURCEMANAGER_EXPORT
				IDataProvider* getDataProvider(const char* name);
				
				RESOURCEMANAGER_EXPORT
				void releaseDataProvider(IDataProvider* data_provider);
				
				RESOURCEMANAGER_EXPORT
				void waitUntilAllDataProvidersReleased();
			
			private:
				
				struct DataProviderWrapper
				{
					IDataProvider* data_provider;
					std::string factory_name;
					int ref_counter = 1;
				};



				std::unordered_map<std::string, IDataProviderFactory*> data_provider_factories;
				std::unordered_map<std::string, DataProviderWrapper> data_providers;
				
				ThreadPool* thread_pool;
				LogHelper logger;
				
				std::condition_variable cv;
			
				typedef std::mutex LockPrimitive;
				LockPrimitive data_providers_mutex;
				LockPrimitive factories_mutex;
		};

#ifdef _MSC_VER
#ifndef ResourceManager_EXPORTS
		extern template class RESOURCEMANAGER_EXPORT Singleton<ResourceManager>;
#else
		template class RESOURCEMANAGER_EXPORT Singleton<ResourceManager>;
#endif
#endif

	} // namespace Core
	
	UNKNOWNENGINE_INLINE
	Core::IDataProvider* CREATE_DATA_PROVIDER(const Core::DataProviderDesc &desc)
	{
		return Core::ResourceManager::getSingleton()->createDataProvider(desc);
	}
	
	UNKNOWNENGINE_INLINE
	Core::IDataProvider* GET_DATA_PROVIDER(const char* name)
	{
		return Core::ResourceManager::getSingleton()->getDataProvider(name);
	}
	
	UNKNOWNENGINE_INLINE
	void RELEASE_DATA_PROVIDER(Core::IDataProvider* data_provider)
	{
		Core::ResourceManager::getSingleton()->releaseDataProvider(data_provider);
	}
	
} // namespace UnknownEngine
