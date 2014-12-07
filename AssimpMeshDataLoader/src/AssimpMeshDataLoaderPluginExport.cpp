#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <AssimpMeshDataLoaderPlugin.h>
#include <Plugins/SubsystemDesc.h>
#include <AssimpMeshDataLoader_export.h>

using namespace UnknownEngine::Loader;
using namespace UnknownEngine::Core;

static AssimpMeshDataLoaderPlugin* instance = nullptr;

extern "C"
ASSIMPMESHDATALOADER_EXPORT
IPlugin* installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	if(!instance) instance = new AssimpMeshDataLoaderPlugin(desc.name.c_str());
	return instance;
}

extern "C"
ASSIMPMESHDATALOADER_EXPORT
void uninstallPlugin(PluginsManager* manager)
{
	if(instance) delete instance;
	instance = nullptr;
}
