#include <stdafx.h>

#include <ESGUIPlugin.h>
#include <ESGUIComponentsFactory.h>
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
			components_factory.reset(new ESGUIComponentsFactory());
			Core::ComponentsManager::getSingleton()->addComponentFactory(components_factory.get());
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
			Core::ComponentsManager::getSingleton()->removeComponentFactory(components_factory.get());
			components_factory.reset();
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
