#pragma once

#include <MessageSystem/Policies/Listener/IMessageReceivePolicyFactory.h>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <MessageSystem/Policies/Listener/IMessageReceivePolicy.h>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseMessageReceivePolicyFactory : public IMessageReceivePolicyFactory
		{
		public:
			virtual IMessageReceivePolicy* createObject ( const MessageReceivePolicyDesc& desc ) override;
			
			virtual void destroyObject ( IMessageReceivePolicy* object ) override;

			virtual bool supportsType ( const MessageReceivePolicyType& object_type ) const override;
			
		protected:
			struct CreatableObjectDesc
			{
				MessageReceivePolicyType type;
				std::function< IMessageReceivePolicy* (const MessageReceivePolicyDesc&) > creator;
				std::function< void (IMessageReceivePolicy*) > deleter;
				
				CreatableObjectDesc():
				deleter( std::default_delete<IMessageReceivePolicy>() ){}
			};

			MESSAGESYSTEM_EXPORT
			void registerCreator(const CreatableObjectDesc& creatable_object_desc);
			
		private:
			std::unordered_set<MessageReceivePolicyType> supported_types;
			std::unordered_map<MessageReceivePolicyType, CreatableObjectDesc> creators;
		};
	}
}