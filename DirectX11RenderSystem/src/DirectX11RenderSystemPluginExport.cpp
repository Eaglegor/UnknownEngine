#include <Plugins/PluginExport.h>
#include <Plugins/PluginsManager.h>
#include "DirectX11RenderSystemPlugin.h"

using namespace UnknownEngine::Graphics;
using namespace UnknownEngine::Core;

static DirectX11RenderSystemPlugin* instance = nullptr;

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void installPlugin(PluginsManager* manager)
{
	instance = new DirectX11RenderSystemPlugin();

	manager->installPlugin(instance);
}

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void uninstallPlugin(PluginsManager* manager)
{
	manager->uninstallPlugin(instance);
}
