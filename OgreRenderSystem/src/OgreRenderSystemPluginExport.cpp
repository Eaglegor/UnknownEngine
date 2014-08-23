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
UnknownEngine::Core::Plugin* installPlugin ( PluginsManager* manager, const SubsystemDesc& desc )
{
	if ( !instance ) instance = new OgreRenderSystemPlugin();
	return instance;
}

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void uninstallPlugin ( PluginsManager* manager )
{
	if ( instance ) delete instance;
	instance = nullptr;
}
