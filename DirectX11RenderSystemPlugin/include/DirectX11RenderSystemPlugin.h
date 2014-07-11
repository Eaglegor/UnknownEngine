#pragma once

/*
 * DirectX10RenderSystemPlugin.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <Plugins/Plugin.h>
#include <InlineSpecification.h>
#include <SubsystemDesc.h>

namespace UnknownEngine
{

	namespace Graphics
	{

		class DirectX11RenderSystemPlugin: public Core::Plugin
		{
			public:
				DirectX11RenderSystemPlugin(HINSTANCE hInstance);
				virtual ~DirectX11RenderSystemPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc &desc) throw (Core::PluginError) override;

				virtual bool init() throw (Core::PluginError) override;

				virtual bool shutdown() throw (Core::PluginError) override;

				virtual bool uninstall() throw (Core::PluginError) override;

			private:
				HINSTANCE hInstance;
				Core::SubsystemDesc desc;

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
