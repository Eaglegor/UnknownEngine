#pragma once

/*
 * PluginsManager.h
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <map>
#include <vector>

#include <PluginError.h>

namespace UnknownEngine
{

	namespace Graphics
	{
		class RenderSystem;
	}

	namespace Core
	{

		class Plugin;

		class PluginsManager
		{
			public:
				PluginsManager ();
				virtual ~PluginsManager ();

				void loadPlugin(std::string library_name) throw(PluginError);

				void installPlugin(Plugin* plugin);
				void uninstallPlugin(Plugin* plugin);

				void addRenderSystem(Graphics::RenderSystem* render_system);
				Graphics::RenderSystem* getRenderSystem(int index);

			private:
				// Generic plugins
				std::vector<Plugin*> plugins;

				// Known subsystems
				std::vector<Graphics::RenderSystem*> render_systems;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
