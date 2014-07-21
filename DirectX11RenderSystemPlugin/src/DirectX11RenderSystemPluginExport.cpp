#include <stdafx.h>

#include <Plugins/PluginExport.h>
#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include "DirectX11RenderSystemPlugin.h"

using namespace UnknownEngine::Graphics;
using namespace UnknownEngine::Core;

static DirectX11RenderSystemPlugin* instance = nullptr;
static HINSTANCE shared_library_handle = nullptr;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH || fdwReason == DLL_THREAD_ATTACH)
	{
		shared_library_handle = hinstDLL;
	}
	else
	{
		shared_library_handle = nullptr;
	}
	return TRUE;
}

extern "C"
UNKNOWNENGINE_PLUGIN_INTERFACE
void installPlugin(PluginsManager* manager, const SubsystemDesc& desc)
{
	instance = new DirectX11RenderSystemPlugin(shared_library_handle);
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