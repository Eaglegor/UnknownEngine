#pragma once

/*
 * OgreRenderSystemPlugin.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <Plugins/Plugin.h>
#include <InlineSpecification.h>
#include <SubsystemDesc.h>

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
	}

	namespace Graphics
	{

		class OgreRenderSystem;
		class OgreRenderableComponentsFactory;

		class OgreRenderSystemPlugin: public Core::Plugin
		{
			public:
				OgreRenderSystemPlugin();
				virtual ~OgreRenderSystemPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc &desc) throw (Core::PluginError) override;

				virtual bool init() throw (Core::PluginError) override;

				virtual bool shutdown() throw (Core::PluginError) override;

				virtual bool uninstall() throw (Core::PluginError) override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext *engine_context;

				OgreRenderSystem* render_system;
				OgreRenderableComponentsFactory* renderable_components_factory;

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
