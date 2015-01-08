#pragma once

#include <InlineSpecification.h>
#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>
#include <LogHelper.h>
#include <memory>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
	}

	namespace GUI
	{
		class CEGuiSubsystemFactory;
		class ICEGuiSubsystem;

		class CEGuiPlugin: public Core::BasePlugin
		{
			public:
				CEGuiPlugin(const char* name);
				virtual ~CEGuiPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				Core::LogHelper logger;
				ICEGuiSubsystem* cegui_subsystem;
				
				std::unique_ptr<CEGuiSubsystemFactory> subsystem_factory;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
