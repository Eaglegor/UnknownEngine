#include <PhysXSubsystemPlugin.h>
#include <Plugins/PluginExport.h>

using namespace UnknownEngine::Physics;
using namespace UnknownEngine::Core;

static PhysXSubsystemPlugin* instance = nullptr;

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new PhysXSubsystemPlugin();
	return instance;
}

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
