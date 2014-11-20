#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <AssimpMeshDataLoaderPlugin.h>
#include <SubsystemDesc.h>
#include <AssimpMeshDataLoader_export.h>

using namespace UnknownEngine::Loader;
using namespace UnknownEngine::Core;

static AssimpMeshDataLoaderPlugin* instance = nullptr;

extern "C"
ASSIMPMESHDATALOADER_EXPORT
UnknownEngine::Core::Plugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new AssimpMeshDataLoaderPlugin();
	return instance;
}

extern "C"
ASSIMPMESHDATALOADER_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
