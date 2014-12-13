#include <stdafx.h>
#include <EndoscopicInstrumentAlgorithmsPlugin.h>
#include <EndoscopicInstrumentAlgorithmsPlugin_export.h>

using namespace UnknownEngine::Endoscopy;
using namespace UnknownEngine::Core;

static EndoscopicInstrumentAlgorithmsPlugin* instance = nullptr;

extern "C"
ENDOSCOPICINSTRUMENTALGORITHMSPLUGIN_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new EndoscopicInstrumentAlgorithmsPlugin(desc.name.c_str());
	return instance;
}

extern "C"
ENDOSCOPICINSTRUMENTALGORITHMSPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
