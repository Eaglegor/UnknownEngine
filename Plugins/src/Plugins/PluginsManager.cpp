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
#include <EngineLogLevel.h>

#ifdef _MSC_VER
	#define __WIN32__
#endif

#ifdef __WIN32__
	#define LOAD_LIBRARY(library_name) LoadLibrary(library_name)
	#define GET_SYMBOL_ADDRESS(library, symbol_name) GetProcAddress( reinterpret_cast<HINSTANCE>(library), symbol_name)
	#define	UNLOAD_LIBRARY(library) FreeLibrary(reinterpret_cast<HINSTANCE>(library))
	#define GET_LAST_LOAD_ERROR() std::string("Error code: " + std::to_string(GetLastError()))
#else
	#include <dlfcn.h>
	#include <link.h>

	#define LOAD_LIBRARY(library_name) dlopen(library_name, RTLD_LAZY)
	#define GET_SYMBOL_ADDRESS(library, symbol_name) dlsym(library, symbol_name)
	#define	UNLOAD_LIBRARY(library) dlclose(library)
	#define GET_LAST_LOAD_ERROR() dlerror()
#endif

#define ENABLE_CORE_SUBSYSTEM_INFO_LOG
#define ENABLE_CORE_SUBSYSTEM_ERROR_LOG
#include <Logging.h>

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		PluginsManager* Singleton<PluginsManager, EngineContext*>::instance = nullptr;

		typedef Plugin* (*PluginStartPoint) ( UnknownEngine::Core::PluginsManager*, const SubsystemDesc &desc);
		typedef void (*PluginShutdownPoint) ( void );

		PluginsManager::PluginsManager (EngineContext* engine_context):
			engine_context(engine_context),
			logger(CREATE_LOGGER("Core.PluginsManager", ENGINE_LOG_LEVEL))
        {
        }

		PluginsManager::~PluginsManager ()
		{
			LOG_INFO(logger, "Shutting down plugins");
			
			for(auto iter = plugins.rbegin(); iter != plugins.rend(); ++iter)
			{
				LOG_INFO(logger, "Shutting down plugin: " + (*iter)->getName());
				(*iter)->shutdown();
			}

			for (auto iter = plugins.rbegin(); iter != plugins.rend(); ++iter)
			{
				LOG_INFO(logger, "Uninstalling plugin: " + (*iter)->getName());
				(*iter)->uninstall();
			}

			plugins.clear();

			LOG_INFO(logger, "Unloading shared libraries");
			for(auto iter = libraries_handlers.rbegin(); iter != libraries_handlers.rend(); ++iter)
			{
				PluginShutdownPoint shutdown_func = reinterpret_cast<PluginShutdownPoint>( GET_SYMBOL_ADDRESS( *iter, "uninstallPlugin" ) );
				shutdown_func();
				UNLOAD_LIBRARY( *iter );
				*iter = nullptr;
			}
			
			RELEASE_LOGGER(logger);
		}

		void PluginsManager::loadSubsystem(const SubsystemDesc &desc)
		{
			LOG_INFO(logger, "Loading subsystem: " + desc.name + " (" + desc.module_name + ")");
			loadModule(desc.module_name, desc);
		}

		void PluginsManager::loadModule (const std::string &library_name, const SubsystemDesc &desc ) 
		{
		  
			LOG_INFO(logger, "Loading shared library " + library_name);
		  
			void* library = LOAD_LIBRARY( library_name.c_str () );

			if ( library == nullptr ) 
			{
			  LOG_ERROR(logger, "Error while loading shared library: " + std::string( GET_LAST_LOAD_ERROR() ));
			  throw UnknownEngine::Core::PluginError ("Library " + library_name + " can't be loaded\n" );
			}
			
			LOG_INFO(logger, "Searching for plugin start point");
			PluginStartPoint start_point = reinterpret_cast< PluginStartPoint > ( GET_SYMBOL_ADDRESS( library , "installPlugin" ) );

			if ( start_point == nullptr ) 
			{
			  LOG_ERROR(logger, "Error while searching entry point: " + std::string(GET_LAST_LOAD_ERROR()));
			  throw UnknownEngine::Core::PluginError (library_name+": Plugin entry point can't be found in library");
			}

			LOG_INFO(logger, "Registering messaging rules");
			MessageDispatcher::getSingleton()->setListenerRules(desc.name, desc.listener_rules);
			MessageDispatcher::getSingleton()->setSenderRules(desc.name, desc.sender_rules);
			LOG_INFO(logger, "Unregistering messaging rules");

			LOG_INFO(logger, "Creating plugin instance: " + library_name);
			Plugin* plugin = start_point ( this, desc );

			LOG_INFO(logger, "Installing plugin: " + library_name);
			
			plugin->setName(desc.name);
			plugin->install(this, desc);

			LOG_INFO(logger, "Installation complete: " + library_name);
			plugins.push_back(plugin);
			libraries_handlers.push_back(library);
		}

		void PluginsManager::initSubsystems ()
		{
			LOG_INFO(logger, "Initializing plugins");
			for(Plugin* plugin: plugins){
				LOG_INFO(logger,  "Initializing plugin: " + plugin->getName());
				plugin->init();
				LOG_INFO(logger,  "Plugin initialized: " + plugin->getName());
			}
		}

		EngineContext *PluginsManager::getEngineContext() const
		{
			return engine_context;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
