#pragma once

/*
 * PluginsManager.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <map>
#include <vector>

#include <ComponentsManager.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>

#include <Plugins/PluginError.h>

namespace UnknownEngine
{

	namespace Graphics
	{
		class RenderSystem;
	}

	namespace Core
	{

		class Plugin;

		class MessageDispatcher;

		class PluginsManager
		{
			public:
				PluginsManager ();
				virtual ~PluginsManager ();

				void loadModule(std::string library_name) throw(PluginError);
				void initPlugins();

				void internalInstallPlugin(Plugin* plugin);
				void internalUninstallPlugin(Plugin* plugin);

				MessageDispatcher* getMessageDispatcher();
				MessageDictionary* getMessageDictionary();
				ComponentsManager* getComponentsManager();

			private:

				MessageDispatcher* message_dispatcher;
				MessageDictionary* message_dictionary;
				ComponentsManager* component_manager;

				std::vector<Plugin*> plugins;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
