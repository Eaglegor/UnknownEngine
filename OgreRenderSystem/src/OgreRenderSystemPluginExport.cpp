#include <stdafx.h>

#include <Plugins/PluginExport.h>
#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <OgreRenderSystemPlugin.h>

using namespace UnknownEngine::Graphics;
using namespace UnknownEngine::Core;

static OgreRenderSystemPlugin* instance = nullptr;

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	instance = new OgreRenderSystemPlugin();
	manager->internalInstallPlugin(instance, desc);
}

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void uninstallPlugin(PluginsManager* manager)
{
	manager->internalUninstallPlugin(instance);
	if(instance) delete instance;
	instance = nullptr;
}
