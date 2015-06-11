#include <stdafx.h>
#include <ESCameraCasePlugin.h>
#include <ESCameraCasePlugin_export.h>

using namespace UnknownEngine::Endoscopy;
using namespace UnknownEngine::Core;

static ESCameraCasePlugin* instance = nullptr;

extern "C"
ESCAMERACASEPLUGIN_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new ESCameraCasePlugin(desc.name.c_str());
	return instance;
}

extern "C"
ESCAMERACASEPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
