#include <stdafx.h>
#include <ESInstrumentHardwarePlugin.h>
#include <ESInstrumentHardwarePlugin_export.h>

using namespace UnknownEngine::Endoscopy;
using namespace UnknownEngine::Core;

static ESInstrumentHardwarePlugin* instance = nullptr;

extern "C"
ESINSTRUMENTHARDWAREPLUGIN_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new ESInstrumentHardwarePlugin(desc.name.c_str());
	return instance;
}

extern "C"
ESINSTRUMENTHARDWAREPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
