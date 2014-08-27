#pragma once

#include <memory>
#include <Objects/IComponent.h>
#include <LogHelper.h>
#include <InlineSpecification.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <MessageSystem/BaseMessageListener.h>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseMessageListener;
		
		class BaseComponent : public IComponent
		{
		public:
			
			BaseComponent ( const std::string& name, EngineContext* engine_context );
			
			virtual void initializeMessageListener(const ReceivedMessageDescriptorsList &received_messages);
			
		protected:

			void registerListener();
			void unregisterListener();
			void flushMessages();
			
			virtual void registerMessageProcessors(BaseMessageListener* message_listener) = 0;

			void initializeLogHelper(const Core::LogMessage::Severity &log_level);
			std::unique_ptr<LogHelper> log_helper;
			
			EngineContext* const engine_context;
			
		private:
			std::unique_ptr<BaseMessageListener> message_listener;
		};
	}
}