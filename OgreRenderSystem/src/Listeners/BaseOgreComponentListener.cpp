#include <Listeners/BaseOgreComponentListener.h>
#include <EngineContext.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		void BaseOgreComponentListener::processMessage ( const UnknownEngine::Core::PackedMessage& msg )
		{
		  (this->*message_processors[msg.getMessageTypeId()])(msg);
		}

		BaseOgreComponentListener<>::BaseOgreComponentListener ( const std::string& object_name ):IMessageListener(object_name)
		{
		}
		
		template <typename ListenerClass>
		template <typename T>
		void BaseOgreComponentListener::registerProcessor(ListenerClass::MessageProcessor processor, Core::EngineContext *engine_context)
		{
			supported_message_type_names.emplace(T::getTypeName());
			Core::MessageType msg_type = engine_context->getMessageDictionary()->getMessageTypeId(T::getTypeName());
			message_processors[msg_type] = processor;
		}
		
		const std::unordered_set< std::string >& BaseOgreComponentListener<>::getSupportedMessageTypeNames()
		{
		  return supported_message_type_names;
		}
		
		bool BaseOgreComponentListener<>::supportsMessageTypeName(const std::string &message_type_name)
		{
		  return supported_message_type_names.find( message_type_name )!=supported_message_type_names.end();
		}
		
	}
}