#pragma once

#include <InlineSpecification.h>
#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>
#include <memory>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
		class ILogger;
	}

	namespace Behavior
	{

		class AngelScriptComponentFactory;

		class AngelScriptSubsystem;

		class AngelScriptPlugin: public Core::BasePlugin
		{
			public:
				AngelScriptPlugin(const char* name);
				virtual ~AngelScriptPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				std::unique_ptr<AngelScriptSubsystem> angel_script_subsystem;
				
				std::unique_ptr<AngelScriptComponentFactory> angel_script_component_factory;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
