#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SimpleBehaviorPlugin.h>
#include <Plugins/SubsystemDesc.h>
#include <SimpleBehaviorPlugin_export.h>

using namespace UnknownEngine::Behavior;
using namespace UnknownEngine::Core;

static SimpleBehaviorPlugin* instance = nullptr;

extern "C"
SIMPLEBEHAVIORPLUGIN_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new SimpleBehaviorPlugin(desc.name.c_str());
	return instance;
}

extern "C"
SIMPLEBEHAVIORPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
