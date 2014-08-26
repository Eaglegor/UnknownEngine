#include <Objects/BaseComponent.h>

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
			log_helper.reset( new LogHelper( getName(), log_level, engine_context) );
		}

		void BaseComponent::initializeMessageListener ( const ReceivedMessagesDesc& received_messages )
		{
			if(received_messages.empty) return;
			message_listener.reset( new BaseMessageListener(getName() + ".Listener", received_messages) );
			this->registerMessageProcessors();
		}

		void BaseComponent::init ( const Entity* parent_entity )
		{
			initComponentImpl(parent_entity);
			if(message_listener) message_listener->registerListener(engine_context->getMessageDispatcher());
		}

		void BaseComponent::shutdown()
		{
			if(message_listener) message_listener->unregisterListener(engine_context->getMessageDispatcher());
			shutdownComponentImpl();
		}
	
	}
}