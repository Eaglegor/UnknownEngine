#pragma once

/*
 * PluginsManager.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <list>
#include <ComponentsManager.h>
#include <Plugins/PluginError.h>

namespace UnknownEngine
{

	namespace Core
	{

		class Plugin;
		class MessageDispatcher;
        class MessageDictionary;
        class ComponentsManager;
		class SubsystemDesc;
        class Engine;

		class PluginsManager
		{
			public:
                PluginsManager (ComponentsManager* components_manager, MessageDispatcher* message_dispatcher, MessageDictionary* message_dictionary);
				virtual ~PluginsManager ();

				void loadSubsystem ( const SubsystemDesc &desc );
				void initSubsystems();

				void internalInstallPlugin(Plugin* plugin);
				void internalUninstallPlugin(Plugin* plugin);

                MessageDispatcher* getMessageDispatcher() const;
                MessageDictionary* getMessageDictionary() const;
                ComponentsManager* getComponentsManager() const;

			private:
				void loadModule(std::string library_name) throw(PluginError);

                MessageDispatcher* const message_dispatcher;
                MessageDictionary* const message_dictionary;
                ComponentsManager* const components_manager;
				std::list<Plugin*> plugins;
				std::list<void*> libraries_handlers;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
