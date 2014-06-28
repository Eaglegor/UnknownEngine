#include <stdafx.h>

#include <Plugins/PluginExport.h>
#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <DummySubsystem.h>
#include <SubsystemDesc.h>

using namespace UnknownEngine::Dummy;
using namespace UnknownEngine::Core;

static DummySubsystemPlugin* instance = nullptr;

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	instance = new DummySubsystemPlugin();
	manager->internalInstallPlugin(instance, desc);
}

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void uninstallPlugin(PluginsManager* manager)
{
	manager->internalUninstallPlugin(instance);
	if(instance) delete instance;
	instance = nullptr;
}
