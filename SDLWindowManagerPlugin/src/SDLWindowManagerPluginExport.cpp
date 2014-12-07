#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SDLWindowManagerPlugin.h>
#include <Plugins/SubsystemDesc.h>
#include <SDLWindowManagerPlugin_export.h>

using namespace UnknownEngine::GUI;
using namespace UnknownEngine::Core;

static SDLWindowManagerPlugin* instance = nullptr;

extern "C"
SDLWINDOWMANAGERPLUGIN_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new SDLWindowManagerPlugin(desc.name.c_str());
	return instance;
}

extern "C"
SDLWINDOWMANAGERPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
