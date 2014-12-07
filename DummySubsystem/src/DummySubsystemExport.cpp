#include <stdafx.h>
#include <DummySubsystem.h>
#include <DummySubsystem_export.h>

using namespace UnknownEngine::Dummy;
using namespace UnknownEngine::Core;

static DummySubsystemPlugin* instance = nullptr;

extern "C"
DUMMYSUBSYSTEM_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new DummySubsystemPlugin(desc.name.c_str());
	return instance;
}

extern "C"
DUMMYSUBSYSTEM_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
