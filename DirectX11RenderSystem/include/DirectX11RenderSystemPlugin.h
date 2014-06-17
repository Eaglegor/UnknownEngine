#pragma once

/*
 * DirectX10RenderSystemPlugin.h
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <Plugins/PluginExport.h>
#include <Plugins/Plugin.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class DirectX11RenderSystemPlugin: public Core::Plugin
		{
			public:
				DirectX11RenderSystemPlugin (HINSTANCE hInstance);
				virtual ~DirectX11RenderSystemPlugin ();

				virtual std::string getName() const;

				virtual bool install (Core::PluginsManager* plugins_manager) throw (Core::PluginError);

				virtual bool init () throw (Core::PluginError);

				virtual bool shutdown () throw (Core::PluginError);

				virtual bool uninstall () throw (Core::PluginError);

			private:
				HINSTANCE hInstance;

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
