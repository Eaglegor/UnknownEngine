#include <stdafx.h>
#include <CEGuiPlugin.h>
#include <CEGuiPlugin_export.h>

using namespace UnknownEngine::GUI;
using namespace UnknownEngine::Core;

static CEGuiPlugin* instance = nullptr;

extern "C"
CEGUIPLUGIN_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new CEGuiPlugin(desc.name.c_str());
	return instance;
}

extern "C"
CEGUIPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
