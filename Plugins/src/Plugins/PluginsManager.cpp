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

//#ifdef __WIN32__
	#define LOAD_LIBRARY(library_name) LoadLibrary(library_name)
	#define GET_SYMBOL_ADDRESS(library, symbol_name) GetProcAddress( reinterpret_cast<HINSTANCE>(library), symbol_name)
	#define	UNLOAD_LIBRARY(library) FreeLibrary(reinterpret_cast<HINSTANCE>(library))
	#define GET_LAST_LOAD_ERROR()
//#else
//	#include <dlfcn.h>
//	#include <link.h>
//
//	#define LOAD_LIBRARY(library_name) dlopen(library_name, RTLD_LAZY)
//	#define GET_SYMBOL_ADDRESS(library, symbol_name) dlsym(library, symbol_name)
//	#define	UNLOAD_LIBRARY(library) dlclose(library)
//	#define GET_LAST_LOAD_ERROR() dlerror()
//#endif

#define ENABLE_CORE_SUBSYSTEM_INFO_LOG
#define ENABLE_CORE_SUBSYSTEM_ERROR_LOG
#include <CoreLogging.h>

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
			CORE_SUBSYSTEM_INFO("Shutting down plugins");
			
			for(auto iter = plugins.rbegin(); iter != plugins.rend(); ++iter)
			{
				CORE_SUBSYSTEM_INFO("Shutting down plugin: " + (*iter)->getName());
				(*iter)->shutdown();
			}
			plugins.clear();

			CORE_SUBSYSTEM_INFO("Unloading shared libraries");
			for(auto iter = libraries_handlers.rbegin(); iter != libraries_handlers.rend(); ++iter)
			{
				PluginShutdownPoint shutdown_func = reinterpret_cast<PluginShutdownPoint>( GET_SYMBOL_ADDRESS( *iter, "uninstallPlugin" ) );
				shutdown_func();
				UNLOAD_LIBRARY( *iter );
				*iter = nullptr;
			}
		}

		void PluginsManager::loadSubsystem(const SubsystemDesc &desc)
		{
			CORE_SUBSYSTEM_INFO("Loading subsystem: " + desc.name + " (" + desc.module_name + ")");
			loadModule(desc.module_name, desc);
		}

		void PluginsManager::loadModule (const std::string &library_name, const SubsystemDesc &desc ) throw ( UnknownEngine::Core::PluginError )
		{
		  
			CORE_SUBSYSTEM_INFO("Loading shared library " + library_name);
		  
			void* library = LOAD_LIBRARY( library_name.c_str () );

			if ( library == nullptr ) 
			{
			  CORE_SUBSYSTEM_ERROR("Error while loading shared library: " + std::string( GET_LAST_LOAD_ERROR() ));
			  throw UnknownEngine::Core::PluginError ("Library " + library_name + " can't be loaded\n" );
			}
			
			CORE_SUBSYSTEM_INFO("Searching for plugin start point");
			PluginStartPoint start_point = reinterpret_cast< PluginStartPoint > ( GET_SYMBOL_ADDRESS( library , "installPlugin" ) );

			if ( start_point == nullptr ) 
			{
			  CORE_SUBSYSTEM_ERROR("Error while searching entry point: " + std::string(GET_LAST_LOAD_ERROR()));
			  throw UnknownEngine::Core::PluginError (library_name+": Plugin entry point can't be found in library");
			}

			CORE_SUBSYSTEM_INFO("Installing module: " + library_name);
			start_point ( this, desc );

			CORE_SUBSYSTEM_INFO("Installation complete: " + library_name);
			libraries_handlers.push_back(library);
		}

		void PluginsManager::initSubsystems ()
		{
			CORE_SUBSYSTEM_INFO("Initializing plugins");
			for(Plugin* plugin: plugins){
				CORE_SUBSYSTEM_INFO( "Initializing plugin: " + plugin->getName());
				plugin->init();
			}
		}

		void PluginsManager::internalInstallPlugin ( Plugin* plugin, const SubsystemDesc &desc )
		{
			CORE_SUBSYSTEM_INFO("Installing plugin: " + desc.name);
			plugins.push_back(plugin);
			plugin->install ( this, desc );
			plugin->setName(desc.name);
		}

		void PluginsManager::internalUninstallPlugin ( Plugin* plugin )
		{
			CORE_SUBSYSTEM_INFO("Uninstalling plugin: " + plugin->getName());
			/// @todo Erase plugin from the list
			plugin->uninstall ();
		}

		EngineContext *PluginsManager::getEngineContext() const
		{
			return engine_context;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
