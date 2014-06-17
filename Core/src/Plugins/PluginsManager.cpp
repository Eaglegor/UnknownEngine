/*
 * PluginsManager.cpp
 *
 *  Created on: 17 ���� 2014 �.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <RenderSystem/RenderSystem.h>

#include <Plugins/Plugin.h>
#include <Plugins/PluginsManager.h>

namespace UnknownEngine
{
	namespace Core
	{

		PluginsManager::PluginsManager ()
		{
			// TODO Auto-generated constructor stub
		}

		PluginsManager::~PluginsManager ()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Core */
} /* namespace UnknownEngine */

void UnknownEngine::Core::PluginsManager::addRenderSystem ( Graphics::RenderSystem* render_system )
{
	this->render_systems.push_back ( render_system );
}

typedef void (*PluginStartPoint) ( UnknownEngine::Core::PluginsManager* );

void UnknownEngine::Core::PluginsManager::loadPlugin ( std::string library_name ) throw ( UnknownEngine::Core::PluginError )
{
	void* library = LoadLibrary ( library_name.c_str () );

	if ( library == nullptr ) throw UnknownEngine::Core::PluginError (library_name, "Library can't be loaded" );

	PluginStartPoint start_point = reinterpret_cast< PluginStartPoint > ( GetProcAddress ( reinterpret_cast< HINSTANCE > ( library ), "installPlugin" ) );

	if ( start_point == nullptr ) throw UnknownEngine::Core::PluginError (library_name, "Plugin entry point can't be found in library");

	start_point ( this );
}

void UnknownEngine::Core::PluginsManager::installPlugin ( Plugin* plugin )
{
	plugin->install ( this );
}

void UnknownEngine::Core::PluginsManager::uninstallPlugin ( Plugin* plugin )
{
	plugin->uninstall ();
}

UnknownEngine::Graphics::RenderSystem* UnknownEngine::Core::PluginsManager::getRenderSystem ( int index )
{
	return render_systems[index];
}