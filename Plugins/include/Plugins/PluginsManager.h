#pragma once

/*
 * PluginsManager.h
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <map>
#include <vector>

#include <ComponentManager.h>
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

				void installPlugin(std::string library_name) throw(PluginError);
				void initPlugins();

				void internalInstallPlugin(Plugin* plugin);
				void internalUninstallPlugin(Plugin* plugin);

				MessageDispatcher* getMessageDispatcher();
				MessageDictionary* getMessageDictionary();
				ComponentManager* getComponentManager();

			private:

				MessageDispatcher* message_dispatcher;
				MessageDictionary* message_dictionary;
				ComponentManager* component_manager;

				std::vector<Plugin*> plugins;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
