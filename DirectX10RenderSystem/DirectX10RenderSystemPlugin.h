#pragma once

/*
 * DirectX10RenderSystemPlugin.h
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <PluginExport.h>
#include <Plugin.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class DirectX10RenderSystemPlugin: public Core::Plugin
		{
			public:
				DirectX10RenderSystemPlugin ();
				virtual ~DirectX10RenderSystemPlugin ();

				virtual std::string getName() const;

				virtual bool install (Core::PluginsManager* plugins_manager) throw (Core::PluginError);

				virtual bool init () throw (Core::PluginError);

				virtual bool shutdown () throw (Core::PluginError);

				virtual bool uninstall () throw (Core::PluginError);

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
