#include <stdafx.h>
#include <ESInstrumentAlgorithmsPlugin.h>
#include <ESInstrumentAlgorithmsPlugin_export.h>

using namespace UnknownEngine::Endoscopy;
using namespace UnknownEngine::Core;

static ESInstrumentAlgorithmsPlugin* instance = nullptr;

extern "C"
ESINSTRUMENTALGORITHMSPLUGIN_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new ESInstrumentAlgorithmsPlugin(desc.name.c_str());
	return instance;
}

extern "C"
ESINSTRUMENTALGORITHMSPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
