#pragma once

#include <memory>
#include <Objects/IComponent.h>
#include <LogHelper.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseMessageListener;
		
		class BaseComponent : public IComponent
		{
		public:
			
			BaseComponent ( const std::string& name, EngineContext* engine_context );
			
			virtual void initializeMessageListener(const ReceivedMessagesDesc &received_messages);
			
			void init ( const Entity* parent_entity ) final;
			void shutdown() final;
			
		protected:
			
			void initImpl ( const Entity* parent_entity ) = 0;
			void shutdownImpl ( ) = 0;
			
			UNKNOWNENGINE_INLINE
			EngineContext* getEngineContext(){return engine_context;}

			virtual void registerMessageProcessors(BaseMessageListener* message_listener){}

			void initializeLogHelper(const Core::LogMessage::Severity &log_level);
			std::unique_ptr<LogHelper> log_helper;
			
		private:
			EngineContext* engine_context;
			std::unique_ptr<BaseMessageListener> message_listener;
		};
	}
}