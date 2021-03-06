#pragma once

#include <InlineSpecification.h>
#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>
#include <LogHelper.h>
#include <ESHardwareControllersManager.h>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
	}

	namespace Endoscopy
	{

		class ESControllersFactory;

		class ESHardwareControllerComponentsFactory;

		class ESInstrumentHardwarePlugin: public Core::BasePlugin
		{
			public:
				ESInstrumentHardwarePlugin(const char* name);
				virtual ~ESInstrumentHardwarePlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				Core::LogHelper logger;
				//ESHardwareControllersManager hardware_manager;
				std::unique_ptr<ESControllersFactory> controllers_factory;
				std::unique_ptr<ESHardwareControllerComponentsFactory> controller_components_factory;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
