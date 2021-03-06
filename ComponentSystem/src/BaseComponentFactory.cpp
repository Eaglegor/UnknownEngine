#include <ComponentSystem/BaseComponentFactory.h>
#include <ComponentSystem/ComponentDesc.h>

namespace UnknownEngine
{
	namespace Core
	{
		IComponent* BaseComponentFactory::createObject ( const ComponentDesc& desc )
		{
			auto iter = creators.find ( desc.type );
			if ( iter == creators.end() ) return nullptr;
			else return iter->second.creator ( desc );
		}
		
		void BaseComponentFactory::destroyObject ( IComponent* object )
		{
			auto iter = creators.find ( object->getType() );
			if ( iter == creators.end() ) return;
			else iter->second.deleter ( object );
		}
		
		bool BaseComponentFactory::supportsType ( const ComponentType& object_type ) const
		{
			return creators.find ( object_type ) != creators.end();
		}
		
		void BaseComponentFactory::registerCreator ( const BaseComponentFactory::CreatableObjectDesc& creatable_object_desc )
		{
			creators[creatable_object_desc.type] = creatable_object_desc;
		}
	}
}