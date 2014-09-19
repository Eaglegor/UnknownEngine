#pragma once

#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Utils
	{
		template<typename OwnerClass>
		class StandardMessageBuffersFactory
		{
		public:
			StandardMessageBuffersFactory(OwnerClass* owner) :
			owner(owner)
			{}
			
			template<typename MessageBufferClass, typename MessageClass>
			MessageBufferClass createBuffer( void (OwnerClass::*processor_method)(const MessageClass&) )
			{
				typedef std::function<void(const MessageClass&)> MessageProcessorClass;
				MessageProcessorClass processor = std::bind( processor_method, owner, std::placeholders::_1 );
				MessageBufferClass buffer(processor);
				return std::move(buffer);
			}
			
		private:
			OwnerClass* owner;

		};
	}
}