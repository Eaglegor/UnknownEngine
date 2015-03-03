#pragma once

#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>
#include <memory>

namespace UnknownEngine
{

	namespace GUI
	{
		class CEGuiContextFactory;

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
				std::unique_ptr<CEGuiContextFactory> context_factory;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
