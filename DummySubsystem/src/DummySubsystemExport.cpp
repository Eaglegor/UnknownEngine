#include <stdafx.h>
#include <DummySubsystem.h>
#include <DummySubsystem_export.h>

using namespace UnknownEngine::Dummy;
using namespace UnknownEngine::Core;

static DummySubsystemPlugin* instance = nullptr;

extern "C"
DUMMYSUBSYSTEM_EXPORT
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new DummySubsystemPlugin();
	return instance;
}

extern "C"
DUMMYSUBSYSTEM_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
