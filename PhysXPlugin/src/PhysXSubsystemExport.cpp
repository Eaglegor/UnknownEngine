#include <stdafx.h>
#include <PhysXSubsystemPlugin.h>
#include <PhysXPlugin_export.h>
#include <Plugins/SubsystemDesc.h>

using namespace UnknownEngine::Physics;
using namespace UnknownEngine::Core;

static PhysXSubsystemPlugin* instance = nullptr;

extern "C"
PHYSXPLUGIN_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new PhysXSubsystemPlugin(desc.name.c_str());
	return instance;
}

extern "C"
PHYSXPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
