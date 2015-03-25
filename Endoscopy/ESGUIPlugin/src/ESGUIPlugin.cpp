#include <stdafx.h>

#include <ESGUIPlugin.h>
#include <Plugins/PluginsManager.h>
#include <Logging.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{

		ESGUIPlugin::ESGUIPlugin(const char* name) :
		Core::BasePlugin(name)
		{
		}

		ESGUIPlugin::~ESGUIPlugin()
		{
		}

		bool ESGUIPlugin::install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)
		{
			return true;
		}

		bool ESGUIPlugin::init()
		{
			return true;
		}

		bool ESGUIPlugin::shutdown()
		{
			return true;
		}

		bool ESGUIPlugin::uninstall()
		{
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
