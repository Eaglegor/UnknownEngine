#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <ConsoleLoggerPlugin.h>
#include <SubsystemDesc.h>
#include <ConsoleLogger_export.h>

using namespace UnknownEngine::Logger;
using namespace UnknownEngine::Core;

static ConsoleLoggerPlugin* instance = nullptr;

extern "C"
CONSOLELOGGER_EXPORT
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new ConsoleLoggerPlugin();
	return instance;
}

extern "C"
CONSOLELOGGER_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
