#include <stdafx.h>
#include <DummySubsystem.h>
#include <Plugins/PluginExport.h>

using namespace UnknownEngine::Dummy;
using namespace UnknownEngine::Core;

static DummySubsystemPlugin* instance = nullptr;

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new DummySubsystemPlugin();
	return instance;
}

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
