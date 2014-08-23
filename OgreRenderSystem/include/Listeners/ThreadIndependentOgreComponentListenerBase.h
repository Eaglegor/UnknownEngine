#pragma once

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/MessageType.h>
#include <unordered_set>
#include <MessageSystem/PackedMessage.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDictionary.h>
#include <InlineSpecification.h>
#include <functional>

#include <OgreRenderSubsystem_fwd.h>

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
	}
	namespace Graphics
	{

		class ThreadIndependentOgreComponentListenerBase : public Core::IMessageListener
		{
			public:


				ThreadIndependentOgreComponentListenerBase ( const std::string& object_name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ):
				IMessageListener ( object_name ),
				render_subsystem(render_subsystem),
				engine_context(engine_context)
				{}
				
				virtual ~ThreadIndependentOgreComponentListenerBase()
				{}

				virtual void processMessage ( const Core::PackedMessage& msg ) = 0;
				
				UNKNOWNENGINE_INLINE
				bool supportsMessageTypeName(const std::string& name)
				{
					return supported_message_type_names.find(name) != supported_message_type_names.end();
				}

			protected:

				std::unordered_set<std::string> supported_message_type_names;

				typedef std::function<void(const Core::PackedMessage&)> MessageProcessor;
				std::unordered_map<Core::MessageType, MessageProcessor> message_processors;

				template<typename T>
				void registerProcessor ( MessageProcessor processor )
				{
					supported_message_type_names.emplace ( T::getTypeName() );
					Core::MessageType msg_type = engine_context->getMessageDictionary()->getMessageTypeId ( T::getTypeName() );
					message_processors[msg_type] = processor;
				}
				
				virtual void internalProcessMessage ( const UnknownEngine::Core::PackedMessage& msg )
				{
					message_processors[msg.getMessageTypeId()] ( msg );
				}
				
				OgreRenderSubsystem* render_subsystem;
				Core::EngineContext* engine_context;
				
		};
	}
}
