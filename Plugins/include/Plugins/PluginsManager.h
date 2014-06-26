#pragma once

/*
 * PluginsManager.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <list>

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
		class SubsystemDesc;

		class PluginsManager
		{
			public:
				PluginsManager ();
				virtual ~PluginsManager ();

				void loadSubsystem ( const SubsystemDesc &desc );
				void initSubsystems();

				void internalInstallPlugin(Plugin* plugin);
				void internalUninstallPlugin(Plugin* plugin);

				MessageDispatcher* getMessageDispatcher();
				MessageDictionary* getMessageDictionary();
				ComponentsManager* getComponentsManager();

			private:
				void loadModule(std::string library_name) throw(PluginError);

				MessageDispatcher* message_dispatcher;
				MessageDictionary* message_dictionary;
				ComponentsManager* component_manager;

				std::list<Plugin*> plugins;
				std::list<void*> libraries_handlers;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
