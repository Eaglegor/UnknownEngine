#pragma once

#include <Plugins/BasePlugin.h>
#include <InlineSpecification.h>
#include <Plugins/SubsystemDesc.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreRenderSubsystemFactory;
		class OgreComponentsFactory;
		class OgreDataProvidersFactory;
		
		class OgreRenderSystemPlugin: public Core::BasePlugin
		{
			public:
				OgreRenderSystemPlugin(const char* name);
				virtual ~OgreRenderSystemPlugin();

				virtual bool install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc &desc )  override;

				virtual bool init()  override;

				virtual bool shutdown()  override;

				virtual bool uninstall()  override;

			private:
				std::unique_ptr<OgreComponentsFactory> components_factory;
				std::unique_ptr<OgreDataProvidersFactory> data_providers_factory;
				
				std::unique_ptr<OgreRenderSubsystemFactory> render_subsystem_factory;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
