/*
 * PluginsManager.cpp
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <RenderSystem.h>

#include "Plugin.h"
#include "PluginsManager.h"

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
	this->render_systems.push_back(render_system);
}

typedef void (*PluginStartPoint)(UnknownEngine::Core::PluginsManager*);

void UnknownEngine::Core::PluginsManager::loadPlugin ( std::string library_name ) throw ( UnknownEngine::Core::PluginError )
{
	void* library = LoadLibrary("libDirectX10RenderSystem.dll");
	PluginStartPoint startPoint = reinterpret_cast<PluginStartPoint> (GetProcAddress( reinterpret_cast<HINSTANCE> (library), "installPlugin"));
	if(startPoint)
	{
		startPoint(this);
	}
}

void UnknownEngine::Core::PluginsManager::installPlugin ( Plugin* plugin )
{
	plugin->install(this);
}

void UnknownEngine::Core::PluginsManager::uninstallPlugin ( Plugin* plugin )
{
	plugin->uninstall();
}

UnknownEngine::Graphics::RenderSystem* UnknownEngine::Core::PluginsManager::getRenderSystem ( int index )
{
	return render_systems[index];
}
