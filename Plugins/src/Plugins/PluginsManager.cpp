/*
 * PluginsManager.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <Plugins/Plugin.h>
#include <Plugins/PluginsManager.h>
#include <MessageSystem/MessageDispatcher.h>
#include <SubsystemDesc.h>
#include <Engine.h>

#ifdef __WIN32__
	#define LOAD_LIBRARY(library_name) LoadLibrary(library_name)
	#define GET_SYMBOL_ADDRESS(library, symbol_name) GetProcAddress( reinterpret_cast<HINSTANCE>(library), symbol_name)
	#define	UNLOAD_LIBRARY(library) FreeLibrary(reinterpret_cast<HINSTANCE>(library))
#else
	#define LOAD_LIBRARY(library_name) dlopen(library_name, RTLD_LAZY)
	#define GET_SYMBOL_ADDRESS(library, symbol_name) dlsym(library, symbol_name)
	#define	UNLOAD_LIBRARY(library) dlclose(library)
#endif

namespace UnknownEngine
{
	namespace Core
	{

		typedef void (*PluginStartPoint) ( UnknownEngine::Core::PluginsManager*, const SubsystemDesc &desc);
		typedef void (*PluginShutdownPoint) ( void );

		PluginsManager::PluginsManager (EngineContext* engine_context):
			engine_context(engine_context)
        {
        }

		PluginsManager::~PluginsManager ()
		{
			for(Plugin* plugin : plugins)
			{
				plugin->shutdown();
			}
			plugins.clear();

			for(void* library : libraries_handlers)
			{
				PluginShutdownPoint shutdown_func = reinterpret_cast<PluginShutdownPoint>( GET_SYMBOL_ADDRESS( library, "uninstallPlugin" ) );
				shutdown_func();
				UNLOAD_LIBRARY( library );
				library = nullptr;
			}
		}

		void PluginsManager::loadSubsystem(const SubsystemDesc &desc)
		{
			loadModule(desc.module_name, desc);
		}

		void PluginsManager::loadModule (const std::string &library_name, const SubsystemDesc &desc ) throw ( UnknownEngine::Core::PluginError )
		{
			void* library = LOAD_LIBRARY( library_name.c_str () );

			if ( library == nullptr ) throw UnknownEngine::Core::PluginError ("Library " + library_name + " can't be loaded" );

			PluginStartPoint start_point = reinterpret_cast< PluginStartPoint > ( GET_SYMBOL_ADDRESS( library , "installPlugin" ) );

			if ( start_point == nullptr ) throw UnknownEngine::Core::PluginError (library_name+": Plugin entry point can't be found in library");

			start_point ( this, desc );

			libraries_handlers.push_back(library);
		}

		void PluginsManager::initSubsystems ()
		{
			for(Plugin* plugin: plugins){
				plugin->init();
			}
		}

		void PluginsManager::internalInstallPlugin ( Plugin* plugin, const SubsystemDesc &desc )
		{
			plugins.push_back(plugin);
			plugin->install ( this, desc );
		}

		void PluginsManager::internalUninstallPlugin ( Plugin* plugin )
		{
			plugin->uninstall ();
		}

		EngineContext *PluginsManager::getEngineContext() const
		{
			return engine_context;
		}


	} /* namespace Core */
} /* namespace UnknownEngine */
