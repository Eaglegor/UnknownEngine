#pragma once

#include <MessageSystem/Policies/Sender/IMessageDeliveryPolicyFactory.h>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <MessageSystem/Policies/Sender/IMessageDeliveryPolicy.h>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseMessageDeliveryPolicyFactory : public IMessageDeliveryPolicyFactory
		{
		public:
			virtual IMessageDeliveryPolicy* createObject ( const MessageDeliveryPolicyDesc& desc ) override;
			
			virtual void destroyObject ( IMessageDeliveryPolicy* object ) override;

			virtual bool supportsType ( const MessageDeliveryPolicyType& object_type ) const override;
			
		protected:
			struct CreatableObjectDesc
			{
				MessageDeliveryPolicyType type;
				std::function< IMessageDeliveryPolicy* (const MessageDeliveryPolicyDesc&) > creator;
				std::function< void (IMessageDeliveryPolicy*) > deleter;
				
				CreatableObjectDesc():
				deleter( std::default_delete<IMessageDeliveryPolicy>() ){}
			};

			MESSAGESYSTEM_EXPORT
			void registerCreator(const CreatableObjectDesc& creatable_object_desc);
			
		private:
			std::unordered_set<MessageDeliveryPolicyType> supported_types;
			std::unordered_map<MessageDeliveryPolicyType, CreatableObjectDesc> creators;
		};
	}
}