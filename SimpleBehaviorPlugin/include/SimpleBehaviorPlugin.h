#pragma once

#include <InlineSpecification.h>
#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>
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

		class SimpleBehaviorPlugin: public Core::BasePlugin
		{
			public:
				SimpleBehaviorPlugin(const char* name);
				virtual ~SimpleBehaviorPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				Core::ILogger* logger;

				std::unique_ptr<SimpleBehaviorsFactory> simple_behaviors_factory;
				
				SimpleBehaviorsPluginDesc plugin_desc;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
