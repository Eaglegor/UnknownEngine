#include <ResourceManager/DataProviders/BaseDataProviderFactory.h>
#include <ResourceManager/DataProviders/DataProviderDesc.h>

namespace UnknownEngine
{
	namespace Core
	{
		IDataProvider* BaseDataProviderFactory::createObject ( const DataProviderDesc& desc )
		{
			auto iter = creators.find ( desc.type );
			if ( iter == creators.end() ) return nullptr;
			else return iter->second.creator ( desc );
		}
		
		void BaseDataProviderFactory::destroyObject ( IDataProvider* object )
		{
			auto iter = creators.find ( object->getType() );
			if ( iter == creators.end() ) return;
			else iter->second.deleter ( object );
		}
		
		bool BaseDataProviderFactory::supportsType ( const DataProviderType& object_type ) const
		{
			return supported_types.find ( object_type ) != supported_types.end();
		}
		
		void BaseDataProviderFactory::registerCreator ( const CreatableObjectDesc& creatable_object_desc )
		{
			supported_types.insert ( creatable_object_desc.type );
			creators[creatable_object_desc.type] = creatable_object_desc;
		}
	}
}