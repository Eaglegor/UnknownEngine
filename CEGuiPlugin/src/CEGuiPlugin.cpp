#include <stdafx.h>

#include <CEGuiPlugin.h>
#include <CEGuiContextFactory.h>
#include <Plugins/PluginsManager.h>
#include <ComponentSystem/ComponentsManager.h>

namespace UnknownEngine
{
	namespace GUI
	{

		CEGuiPlugin::CEGuiPlugin(const char* name):
		Core::BasePlugin(name)
		{
		}

		CEGuiPlugin::~CEGuiPlugin()
		{
		}

		bool CEGuiPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
			context_factory.reset(new CEGuiContextFactory());
			Core::ComponentsManager::getSingleton()->addComponentFactory(context_factory.get());
			return true;
		}

		bool CEGuiPlugin::init () 
		{
			return true;
		}

		bool CEGuiPlugin::shutdown () 
		{
			return true;
		}

		bool CEGuiPlugin::uninstall () 
		{
			Core::ComponentsManager::getSingleton()->removeComponentFactory(context_factory.get());		  
			context_factory.reset();
			return true;
		}
		
	} /* namespace Graphics */
} /* namespace UnknownEngine */
