#pragma once

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/MessageType.h>
#include <unordered_set>
#include <MessageSystem/PackedMessage.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDictionary.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
	}
	namespace Graphics
	{
		template <typename ListenerClass>
		class BaseOgreComponentListener : public UnknownEngine::Core::IMessageListener
		{
			public:
				virtual void processMessage ( const UnknownEngine::Core::PackedMessage& msg )
				{
				  ( static_cast<ListenerClass*>(this)->*message_processors[msg.getMessageTypeId()])(msg);
				}

				UNKNOWNENGINE_INLINE
				const std::unordered_set<std::string>& getSupportedMessageTypeNames()
				{
					return supported_message_type_names;
				}
				
				UNKNOWNENGINE_INLINE
				bool supportsMessageTypeName ( const std::string &message_type_name )
				{
					return supported_message_type_names.find ( message_type_name ) != supported_message_type_names.end();
				}

				BaseOgreComponentListener ( const std::string& object_name ):IMessageListener(object_name){};

			protected:

				std::unordered_set<std::string> supported_message_type_names;

				typedef void ( ListenerClass::*MessageProcessor ) ( const Core::PackedMessage& );
				std::unordered_map<Core::MessageType, MessageProcessor> message_processors;

				template<typename T>
				void registerProcessor ( MessageProcessor processor, Core::EngineContext* engine_context )
				{
					supported_message_type_names.emplace ( T::getTypeName() );
					Core::MessageType msg_type = engine_context->getMessageDictionary()->getMessageTypeId ( T::getTypeName() );
					message_processors[msg_type] = processor;
				}

		};
	}
}