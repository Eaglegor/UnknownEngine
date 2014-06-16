#include <PluginExport.h>
#include <PluginsManager.h>
#include "DirectX10RenderSystemPlugin.h"

using namespace UnknownEngine::Graphics;
using namespace UnknownEngine::Core;

static DirectX10RenderSystemPlugin* instance = nullptr;

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void installPlugin(PluginsManager* manager)
{
	instance = new DirectX10RenderSystemPlugin();

	manager->installPlugin(instance);
}

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void uninstallPlugin(PluginsManager* manager)
{
	manager->uninstallPlugin(instance);
}
