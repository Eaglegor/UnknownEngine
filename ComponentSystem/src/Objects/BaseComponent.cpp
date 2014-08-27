#include <Objects/BaseComponent.h>
#include <MessageSystem/BaseMessageListener.h>

namespace UnknownEngine
{
	namespace Core
	{
		BaseComponent::BaseComponent ( const std::string& name, EngineContext* engine_context ) : 
		IComponent ( name ),
		engine_context(engine_context)
		{

		}

		void BaseComponent::initializeLogHelper ( const LogMessage::Severity& log_level )
		{
			if(log_level > LogMessage::Severity::LOG_SEVERITY_NONE)
			{
				log_helper.reset( new LogHelper( getName(), log_level, engine_context) );
			}
		}

		void BaseComponent::initializeMessageListener ( const UnknownEngine::Core::ReceivedMessageDescriptorsList& received_messages )
		{
			if(received_messages.empty()) return;
			message_listener.reset( new BaseMessageListener(getName() + ".Listener", engine_context) );
			message_listener->setSupportedMessageTypes(received_messages);
			this->registerMessageProcessors(message_listener.get());
		}

		void BaseComponent::registerListener()
		{
			if(message_listener) message_listener->registerListener(engine_context->getMessageDispatcher());
		}

		void BaseComponent::unregisterListener()
		{
			if(message_listener) message_listener->unregisterListener(engine_context->getMessageDispatcher());
		}
		
		void BaseComponent::flushMessages()
		{
			if(message_listener) message_listener->flushAllMessageBuffers();
		}
		
	}
}