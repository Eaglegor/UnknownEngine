#pragma once

/*
 * PluginsManager.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <list>
#include <Plugins/PluginError.h>

namespace UnknownEngine
{

	namespace Core
	{

		class Plugin;
		class SubsystemDesc;
		class EngineContext;

		class PluginsManager
		{
			public:
				PluginsManager (EngineContext* engine_context);
				virtual ~PluginsManager ();

				void loadSubsystem ( const SubsystemDesc &desc );
				void initSubsystems();

				void internalInstallPlugin(Plugin* plugin, const SubsystemDesc &desc);
				void internalUninstallPlugin(Plugin* plugin);

				EngineContext* getEngineContext() const;

			private:
				void loadModule(const std::string &library_name, const SubsystemDesc &desc) throw(PluginError);

				EngineContext* engine_context;
				std::list<Plugin*> plugins;
				std::list<void*> libraries_handlers;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
