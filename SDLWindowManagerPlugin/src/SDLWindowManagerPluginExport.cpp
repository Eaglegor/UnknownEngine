#include <stdafx.h>

#include <Plugins/PluginExport.h>
#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SDLWindowManagerPlugin.h>
#include <SubsystemDesc.h>

using namespace UnknownEngine::GUI;
using namespace UnknownEngine::Core;

static SDLWindowManagerPlugin* instance = nullptr;

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new SDLWindowManagerPlugin();
	return instance;
}

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}