#include <stdafx.h>

#include <ESCameraCasePlugin.h>
#include <Plugins/PluginsManager.h>
#include <Logging.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{

		ESCameraCasePlugin::ESCameraCasePlugin(const char* name) :
		Core::BasePlugin(name)
		{
		}

		ESCameraCasePlugin::~ESCameraCasePlugin()
		{
		}

		bool ESCameraCasePlugin::install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)
		{
			return true;
		}

		bool ESCameraCasePlugin::init()
		{
			return true;
		}

		bool ESCameraCasePlugin::shutdown()
		{
			return true;
		}

		bool ESCameraCasePlugin::uninstall()
		{
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
