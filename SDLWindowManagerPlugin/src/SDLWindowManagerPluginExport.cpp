#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SDLWindowManagerPlugin.h>
#include <SubsystemDesc.h>
#include <SDLWindowManagerPlugin_export.h>

using namespace UnknownEngine::GUI;
using namespace UnknownEngine::Core;

static SDLWindowManagerPlugin* instance = nullptr;

extern "C"
SDLWINDOWMANAGERPLUGIN_EXPORT
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new SDLWindowManagerPlugin();
	return instance;
}

extern "C"
SDLWINDOWMANAGERPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
