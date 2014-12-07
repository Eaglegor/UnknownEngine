#pragma once

#include <ResourceManager_export.h>
#include <unordered_map>
#include <Singleton.h>
#include <LogHelper.h>
#include <mutex>

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
				void removeDataProvider ( IDataProvider* data_provider );

				RESOURCEMANAGER_EXPORT
				void cleanup();

			private:
				void internalCleanup(bool force_destruction);
				void internalRemoveDataProvider(IDataProvider* data_provider, bool force_destruction = false);
				
				std::unordered_map<std::string, IDataProviderFactory*> data_provider_factories;
				std::unordered_map<std::string, IDataProvider*> data_providers;
				
				ThreadPool* thread_pool;
				LogHelper logger;
				
				typedef std::mutex LockPrimitive;
				LockPrimitive mutex;
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
