#pragma once

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/MessageType.h>
#include <unordered_set>
#include <MessageSystem/PackedMessage.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDictionary.h>
#include <InlineSpecification.h>

#include <OgreRenderSubsystem.h>

#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
	#include <tbb/concurrent_queue.h>
#endif

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
	}
	namespace Graphics
	{

		class OgreRenderSubsystem;
		template <typename ListenerClass>
		class BaseOgreComponentListener : public UnknownEngine::Core::IMessageListener
		{
			public:

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

				BaseOgreComponentListener ( const std::string& object_name, OgreRenderSubsystem* render_subsystem ):
				IMessageListener ( object_name ),
				render_subsystem(render_subsystem)
				{
					
				#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
					if(render_subsystem->hasSeparateRenderThreadEnabled())
					{
						render_subsystem->addSynchronizeCallback(getName(), [this](){this->processAllQueuedMessages();});
					}
				#endif

				}
				
				virtual ~BaseOgreComponentListener()
				{
					/*if(render_subsystem->hasSeparateRenderThreadEnabled())
					{
						render_subsystem->removeSynchronizeCallback(getName());
					}*/
				}

				virtual void processMessage ( const Core::PackedMessage& msg )
				{
				#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
					if(render_subsystem->hasSeparateRenderThreadEnabled())
					{
						messages_queue.push(msg);
					}
					else
				#endif
						internalProcessMessage(msg);
				}

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
				
			private:
				
				virtual void internalProcessMessage ( const UnknownEngine::Core::PackedMessage& msg )
				{
					( static_cast<ListenerClass*> ( this )->*message_processors[msg.getMessageTypeId()] ) ( msg );
				}
				
				OgreRenderSubsystem* render_subsystem;
				
#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
				tbb::concurrent_queue<Core::PackedMessage> messages_queue;
				
				void processAllQueuedMessages()
				{
					Core::PackedMessage current_msg;
					while(messages_queue.try_pop(current_msg))
					{
						internalProcessMessage(current_msg);
					}
				}
#endif

		};
	}
}
