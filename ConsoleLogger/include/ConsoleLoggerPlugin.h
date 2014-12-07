#pragma once

#include <Plugins/BasePlugin.h>
#include <InlineSpecification.h>
#include <Plugins/SubsystemDesc.h>
#include <ConsoleLogger.h>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
	}

	namespace Logger
	{

		class ConsoleLoggerPlugin: public Core::BasePlugin
		{
			public:
				ConsoleLoggerPlugin(const char* name);
				virtual ~ConsoleLoggerPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				std::unique_ptr<ConsoleLogger> console_logger;

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
