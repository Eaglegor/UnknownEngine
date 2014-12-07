#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <OgreRenderSystemPlugin.h>
#include <OgreRenderSystem_export.h>

using namespace UnknownEngine::Graphics;
using namespace UnknownEngine::Core;

static OgreRenderSystemPlugin* instance = nullptr;

extern "C"
OGRERENDERSYSTEM_EXPORT
IPlugin* installPlugin ( PluginsManager* manager, const SubsystemDesc& desc )
{
	if ( !instance ) instance = new OgreRenderSystemPlugin(desc.name.c_str());
	return instance;
}

extern "C"
OGRERENDERSYSTEM_EXPORT
void uninstallPlugin ( PluginsManager* manager )
{
	if ( instance ) delete instance;
	instance = nullptr;
}
