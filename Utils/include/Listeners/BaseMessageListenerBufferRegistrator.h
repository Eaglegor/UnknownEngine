#pragma once
#include <MessageSystem/BaseMessageListener.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename OwnerClass>
		class BaseMessageListenerBufferRegistrator
		{
		public:
			BaseMessageListenerBufferRegistrator(Core::BaseMessageListener* listener, OwnerClass* owner):
			listener(listener),
			owner(owner)
			{}
			
			template<typename MessageClass, typename StandardMessageBufferClass>
			void registerStandardMessageBuffer( void (OwnerClass::*processor_method)(const MessageClass&) )
			{
				typedef std::function<void(const MessageClass&)> MessageProcessorClass;
				MessageProcessorClass processor = std::bind( processor_method, owner, std::placeholders::_1 );
				StandardMessageBufferClass buffer(processor);
				listener->registerMessageBuffer( MESSAGE_TYPE_ID(MessageClass::getTypeName()), buffer );
			}
			
		private:
			Core::BaseMessageListener* listener;
			OwnerClass* owner;

		};
	}
}