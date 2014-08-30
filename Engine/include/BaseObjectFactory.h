#pragma once

#include <AbstractObjectFactory.h>
#include <unordered_map>
#include <functional>
#include <memory>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Core
	{
		template <typename ObjectType, typename ObjectTypeId, typename DescriptorClass>
		class BaseObjectFactory : public AbstractObjectFactory<ObjectType, ObjectTypeId, DescriptorClass>
		{
		public:
			
			virtual ObjectType* createObject ( const DescriptorClass& desc )
			{
				auto iter = component_creators.find ( desc.type );
				if ( iter == component_creators.end() ) return nullptr;
				else return iter->second.creator ( desc );
			}
			
			virtual void destroyObject ( ObjectType* object )
			{
				auto iter = component_creators.find ( object->getType() );
				if ( iter == component_creators.end() ) return;
				else iter->second.deleter ( object );
			}

			UNKNOWNENGINE_INLINE
			virtual bool supportsType ( const ObjectTypeId& object_type )
			{
				return supported_types.find ( object_type ) != supported_types.end();
			}
			
			virtual const std::unordered_set< ObjectTypeId >& getSupportedTypes()
			{
				return supported_types;
			}
			
		protected:
			
			struct CreatableObjectDesc
			{
				ObjectTypeId type;
				std::function< ObjectType* (const DescriptorClass&) > creator;
				std::function< void (ObjectType*) > deleter;
				
				CreatableObjectDesc():
				deleter( std::default_delete<ObjectType>() ){}
			};

			void registerCreator(const CreatableObjectDesc& creatable_object_desc)
			{
				supported_types.insert(creatable_object_desc.type);
				component_creators[creatable_object_desc.type] = creatable_object_desc;
			}
			
			std::unordered_set<ObjectTypeId> supported_types;
			std::unordered_map<ObjectTypeId, CreatableObjectDesc> component_creators;
			
		};
	}
}