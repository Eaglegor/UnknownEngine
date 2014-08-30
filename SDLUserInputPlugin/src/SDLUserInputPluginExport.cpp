#include <stdafx.h>

#include <Plugins/PluginExport.h>
#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SDLUserInputPlugin.h>
#include <SubsystemDesc.h>

using namespace UnknownEngine::IO;
using namespace UnknownEngine::Core;

static SDLUserInputPlugin* instance = nullptr;

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new SDLUserInputPlugin();
	return instance;
}

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
