#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <ResourceManager/DataProviders/IDataProviderFactory.h>
#include <ResourceManager/DataProviders/IDataProvider.h>

namespace UnknownEngine
{
	namespace Core
	{
		class IDataProvider;		
		
		class BaseDataProviderFactory : public IDataProviderFactory
		{
		public:
			RESOURCEMANAGER_EXPORT
			virtual IDataProvider* createObject ( const DataProviderDesc& desc ) override;
			
			RESOURCEMANAGER_EXPORT
			virtual void destroyObject ( IDataProvider* object ) override;

			RESOURCEMANAGER_EXPORT
			virtual bool supportsType ( const DataProviderType& object_type ) const override;
			
		protected:
			struct CreatableObjectDesc
			{
				DataProviderType type;
				std::function< IDataProvider* (const DataProviderDesc&) > creator;
				std::function< void (IDataProvider*) > deleter;
				
				CreatableObjectDesc():
				deleter( std::default_delete<IDataProvider>() ){}
			};

			RESOURCEMANAGER_EXPORT
			void registerCreator(const CreatableObjectDesc& creatable_object_desc);
			
		private:
			std::unordered_set<DataProviderType> supported_types;
			std::unordered_map<DataProviderType, CreatableObjectDesc> creators;
		};
	}
}