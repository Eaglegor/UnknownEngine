#include <stdafx.h>
#include <InputContextMapperPlugin.h>
#include <Plugins/PluginExport.h>

using namespace UnknownEngine::IO;
using namespace UnknownEngine::Core;

static InputContextMapperPlugin* instance = nullptr;

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
    if(!instance) instance = new InputContextMapperPlugin();
    return instance;
}

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void uninstallPlugin(PluginsManager* manager)
{
    if(instance) delete instance;
    instance = nullptr;
}
