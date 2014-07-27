#pragma once

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/MessageType.h>
#include <unordered_set>
#include <MessageSystem/PackedMessage.h>

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

				const std::unordered_set<std::string>& getSupportedMessageTypeNames();
				
				bool supportsMessageTypeName ( const std::string &message_type_name );

				BaseOgreComponentListener ( const std::string& object_name );

			protected:

				static std::unordered_set<std::string> supported_message_type_names;

				typedef void ( ListenerClass::*MessageProcessor ) ( const Core::PackedMessage& );
				std::unordered_map<Core::MessageType, MessageProcessor> message_processors;

				template<typename T>
				void registerProcessor ( MessageProcessor processor, Core::EngineContext* engine_context );

		};
	}
}