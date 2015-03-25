#include <stdafx.h>
#include <ESGUIPlugin.h>
#include <ESGUIPlugin_export.h>

using namespace UnknownEngine::Endoscopy;
using namespace UnknownEngine::Core;

static ESGUIPlugin* instance = nullptr;

extern "C"
ESGUIPLUGIN_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new ESGUIPlugin(desc.name.c_str());
	return instance;
}

extern "C"
ESGUIPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
