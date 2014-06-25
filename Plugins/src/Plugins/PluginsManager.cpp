/*
 * PluginsManager.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <Plugins/Plugin.h>
#include <Plugins/PluginsManager.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine
{
	namespace Core
	{

		PluginsManager::PluginsManager ()
		{
			message_dictionary = MessageDictionary::getSingleton();
			message_dispatcher = MessageDispatcher::getSingleton();
			component_manager = ComponentsManager::getSingleton();
		}

		PluginsManager::~PluginsManager ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */

typedef void (*PluginStartPoint) ( UnknownEngine::Core::PluginsManager* );

void UnknownEngine::Core::PluginsManager::loadModule ( std::string library_name ) throw ( UnknownEngine::Core::PluginError )
{
	void* library = LoadLibrary ( library_name.c_str () );

	if ( library == nullptr ) throw UnknownEngine::Core::PluginError ("Library " + library_name + " can't be loaded" );

	PluginStartPoint start_point = reinterpret_cast< PluginStartPoint > ( GetProcAddress ( reinterpret_cast< HINSTANCE > ( library ), "installPlugin" ) );

	if ( start_point == nullptr ) throw UnknownEngine::Core::PluginError (library_name+": Plugin entry point can't be found in library");

	start_point ( this );
}

void UnknownEngine::Core::PluginsManager::initPlugins ()
{
	for(Plugin* plugin: plugins){
		plugin->init();
	}
}

void UnknownEngine::Core::PluginsManager::internalInstallPlugin ( Plugin* plugin )
{
	plugins.push_back(plugin);
	plugin->install ( this );
}

void UnknownEngine::Core::PluginsManager::internalUninstallPlugin ( Plugin* plugin )
{
	plugin->uninstall ();
}

UnknownEngine::Core::MessageDispatcher* UnknownEngine::Core::PluginsManager::getMessageDispatcher ()
{
	return message_dispatcher;
}

UnknownEngine::Core::MessageDictionary* UnknownEngine::Core::PluginsManager::getMessageDictionary ()
{
	return message_dictionary;
}

UnknownEngine::Core::ComponentsManager* UnknownEngine::Core::PluginsManager::getComponentsManager ()
{
	return component_manager;
}
