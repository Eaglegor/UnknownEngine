#include <Listeners/BaseOgreComponentListener.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		template<typename ListenerClass>
		BaseOgreComponentListener<ListenerClass>::BaseOgreComponentListener ( const std::string& object_name ) : IMessageListener ( object_name )
		{}

		template<typename ListenerClass>
		const std::unordered_set< std::string >& BaseOgreComponentListener<ListenerClass>::getSupportedMessageTypeNames()
		{
			return supported_message_type_names;
		}

		template<typename ListenerClass>
		template<typename T>
		void BaseOgreComponentListener<ListenerClass>::registerProcessor ( MessageProcessor processor, Core::EngineContext* engine_context )
		{
			supported_message_type_names.emplace ( T::getTypeName() );
			Core::MessageType msg_type = engine_context->getMessageDictionary()->getMessageTypeId ( T::getTypeName() );
			message_processors[msg_type] = processor;
		}

		template<typename ListenerClass>
		bool BaseOgreComponentListener<ListenerClass>::supportsMessageTypeName ( const std::string& message_type_name )
		{
			return supported_message_type_names.find ( message_type_name ) != supported_message_type_names.end();
		}


	}
}