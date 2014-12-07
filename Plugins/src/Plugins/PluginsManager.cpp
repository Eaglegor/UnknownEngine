#include <stdafx.h>

#include <Plugins/IPlugin.h>
#include <Plugins/PluginsManager.h>
#include <MessageSystem/MessageDispatcher.h>
#include <Plugins/SubsystemDesc.h>
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

		typedef IPlugin* (*PluginStartPoint) ( UnknownEngine::Core::PluginsManager*, const SubsystemDesc &desc);
		typedef void (*PluginShutdownPoint) ( void );

		PluginsManager::PluginsManager (EngineContext* engine_context):
			engine_context(engine_context),
			logger("Core.PluginsManager", ENGINE_LOG_LEVEL)
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
		}

		bool PluginsManager::loadSubsystem(const SubsystemDesc &desc)
		{
			LOG_INFO(logger, "Loading subsystem: " + desc.name + " (" + desc.module_name + ")");
			return loadModule(desc.module_name.c_str(), desc);
		}

		bool PluginsManager::loadModule (const char* library_name, const SubsystemDesc &desc ) 
		{
			LOG_INFO(logger, "Loading shared library " + library_name);
		  
			void* library = LOAD_LIBRARY( library_name );

			if ( library == nullptr ) 
			{
			  LOG_ERROR(logger, "Error while loading shared library: " + std::string( GET_LAST_LOAD_ERROR() ));
			  return false;
			}
			
			LOG_INFO(logger, "Searching for plugin start point");
			PluginStartPoint start_point = reinterpret_cast< PluginStartPoint > ( GET_SYMBOL_ADDRESS( library , "installPlugin" ) );

			if ( start_point == nullptr ) 
			{
			  LOG_ERROR(logger, "Error while searching entry point: " + std::string(GET_LAST_LOAD_ERROR()));
			  return false;
			}

			LOG_INFO(logger, "Registering messaging rules");
			MessageDispatcher::getSingleton()->setListenerRules(desc.name.c_str(), desc.listener_rules);
			MessageDispatcher::getSingleton()->setSenderRules(desc.name.c_str(), desc.sender_rules);
			LOG_INFO(logger, "Unregistering messaging rules");

			LOG_INFO(logger, "Creating plugin instance: " + library_name);
			IPlugin* plugin = start_point ( this, desc );

			LOG_INFO(logger, "Installing plugin: " + library_name);
			
			plugin->install(this, desc);

			LOG_INFO(logger, "Installation complete: " + library_name);
			plugins.push_back(plugin);
			libraries_handlers.push_back(library);
			
			return true;
		}

		void PluginsManager::initSubsystems ()
		{
			LOG_INFO(logger, "Initializing plugins");
			for(IPlugin* plugin: plugins){
				LOG_INFO(logger,  "Initializing plugin: " + plugin->getName());
				plugin->init();
				LOG_INFO(logger,  "Plugin initialized: " + plugin->getName());
			}
		}

		EngineContext* PluginsManager::getEngineContext() const
		{
			return engine_context;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
