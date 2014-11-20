#include <stdafx.h>
#include <AngelScriptPlugin.h>
#include <AngelScriptPlugin_export.h>

using namespace UnknownEngine::Behavior;
using namespace UnknownEngine::Core;

static AngelScriptPlugin* instance = nullptr;

extern "C"
ANGELSCRIPTPLUGIN_EXPORT
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new AngelScriptPlugin();
	return instance;
}

extern "C"
ANGELSCRIPTPLUGIN_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
