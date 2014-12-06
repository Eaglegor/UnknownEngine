#pragma once

#include <InlineSpecification.h>
#include <Plugins/Plugin.h>
#include <SubsystemDesc.h>
#include <Descriptors/SimpleBehaviorsPluginDesc.h>

namespace UnknownEngine
{
	namespace IO
	{

		struct KeyStateChangedMessage;
	}


	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
		class BaseMessageListener;
		struct UpdateFrameMessage;
		template<class MessageClass >
		class MessageSender;
		struct StopEngineActionMessage;
		class ILogger;
	}

	namespace Utils
	{
		class ILogger;
	}
	
	namespace Behavior
	{

		class SimpleBehaviorsPerformer;

		class SimpleBehaviorsFactory;

		class SimpleBehaviorPlugin: public Core::Plugin
		{
			public:
				SimpleBehaviorPlugin();
				virtual ~SimpleBehaviorPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;
				
				void onUpdateFrame(const Core::UpdateFrameMessage& msg);
				void stopEngine();

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				Core::ILogger* logger;

				std::unique_ptr<Core::MessageSender<Core::StopEngineActionMessage> > stop_engine_message_sender;
				
				std::unique_ptr<SimpleBehaviorsPerformer> behaviors_performer;
				std::unique_ptr<Core::BaseMessageListener> listener;
				std::unique_ptr<SimpleBehaviorsFactory> simple_behaviors_factory;
				
				SimpleBehaviorsPluginDesc plugin_desc;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
