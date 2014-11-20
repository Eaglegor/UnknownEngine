#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SimpleBehaviorPlugin.h>
#include <SubsystemDesc.h>
#include <SimpleBehaviorPlugin_export.h>

using namespace UnknownEngine::Behavior;
using namespace UnknownEngine::Core;

static SimpleBehaviorPlugin* instance = nullptr;

extern "C"
SIMPLEBEHAVIORPLUGIN_EXPORT
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new SimpleBehaviorPlugin();
	return instance;
}

extern "C"
SIMPLEBEHAVIORPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
