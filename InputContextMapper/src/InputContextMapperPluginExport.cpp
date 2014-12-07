#include <stdafx.h>
#include <InputContextMapperPlugin.h>
#include <InputContextMapper_export.h>

using namespace UnknownEngine::IO;
using namespace UnknownEngine::Core;

static InputContextMapperPlugin* instance = nullptr;

extern "C"
INPUTCONTEXTMAPPER_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
    if(!instance) instance = new InputContextMapperPlugin(desc.name.c_str());
    return instance;
}

extern "C"
INPUTCONTEXTMAPPER_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
    if(instance) delete instance;
    instance = nullptr;
}
