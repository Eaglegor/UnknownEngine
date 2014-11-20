#include <stdafx.h>
#include <PhysXSubsystemPlugin.h>
#include <PhysXPlugin_export.h>

using namespace UnknownEngine::Physics;
using namespace UnknownEngine::Core;

static PhysXSubsystemPlugin* instance = nullptr;

extern "C"
PHYSXPLUGIN_EXPORT
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new PhysXSubsystemPlugin();
	return instance;
}

extern "C"
PHYSXPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
