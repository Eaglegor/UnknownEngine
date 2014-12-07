#include <MessageSystem/Policies/Listener/BaseMessageReceivePolicyFactory.h>
#include <MessageSystem/Policies/Listener/MessageReceivePolicyDesc.h>

namespace UnknownEngine
{
	namespace Core
	{
		IMessageReceivePolicy* BaseMessageReceivePolicyFactory::createObject ( const MessageReceivePolicyDesc& desc )
		{
			auto iter = component_creators.find ( desc.type );
			if ( iter == component_creators.end() ) return nullptr;
			else return iter->second.creator ( desc );
		}
		
		void BaseMessageReceivePolicyFactory::destroyObject ( IMessageReceivePolicy* object )
		{
			auto iter = component_creators.find ( object->getType() );
			if ( iter == component_creators.end() ) return;
			else iter->second.deleter ( object );
		}
		
		bool BaseMessageReceivePolicyFactory::supportsType ( const MessageReceivePolicyType& object_type ) const
		{
			return supported_types.find ( object_type ) != supported_types.end();
		}
		
		void BaseMessageReceivePolicyFactory::registerCreator ( const CreatableObjectDesc& creatable_object_desc )
		{
			supported_types.insert ( creatable_object_desc.type );
			component_creators[creatable_object_desc.type] = creatable_object_desc;
		}
	}
}