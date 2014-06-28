#include <stdafx.h>

#include <Plugins/PluginExport.h>
#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <ConsoleLoggerPlugin.h>
#include <SubsystemDesc.h>

using namespace UnknownEngine::Logger;
using namespace UnknownEngine::Core;

static ConsoleLoggerPlugin* instance = nullptr;

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	instance = new ConsoleLoggerPlugin();
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
