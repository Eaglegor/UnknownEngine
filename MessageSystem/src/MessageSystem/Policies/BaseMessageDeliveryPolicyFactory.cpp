#include <MessageSystem/Policies/Sender/BaseMessageDeliveryPolicyFactory.h>
#include <MessageSystem/Policies/Sender/MessageDeliveryPolicyDesc.h>

namespace UnknownEngine
{
	namespace Core
	{
		IMessageDeliveryPolicy* BaseMessageDeliveryPolicyFactory::createObject ( const MessageDeliveryPolicyDesc& desc )
		{
			auto iter = component_creators.find ( desc.type );
			if ( iter == component_creators.end() ) return nullptr;
			else return iter->second.creator ( desc );
		}
		
		void BaseMessageDeliveryPolicyFactory::destroyObject ( IMessageDeliveryPolicy* object )
		{
			auto iter = component_creators.find ( object->getType() );
			if ( iter == component_creators.end() ) return;
			else iter->second.deleter ( object );
		}
		
		bool BaseMessageDeliveryPolicyFactory::supportsType ( const MessageDeliveryPolicyType& object_type ) const
		{
			return supported_types.find ( object_type ) != supported_types.end();
		}
		
		void BaseMessageDeliveryPolicyFactory::registerCreator ( const CreatableObjectDesc& creatable_object_desc )
		{
			supported_types.insert ( creatable_object_desc.type );
			component_creators[creatable_object_desc.type] = creatable_object_desc;
		}
	}
}