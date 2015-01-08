#include <stdafx.h>

#include <CEGuiPlugin.h>
#include <CEGuiSubsystemFactory.h>
#include <Plugins/PluginsManager.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace GUI
	{

		CEGuiPlugin::CEGuiPlugin(const char* name):
		Core::BasePlugin(name),
		logger(name, Core::LogSeverity::NONE),
		cegui_subsystem(nullptr)
		{
		}

		CEGuiPlugin::~CEGuiPlugin()
		{
		}

		bool CEGuiPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
			LOG_INFO(logger, "Logger initialized");
			
			LOG_INFO(logger, "Installing CEGUI plugin");

			LOG_INFO(logger, "Creating CEGUI factory");
			subsystem_factory.reset(new CEGuiSubsystemFactory(logger));
			
			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool CEGuiPlugin::init () 
		{
			LOG_INFO(logger, "Initializing CEGUI plugin");

			LOG_INFO(logger, "Creating CEGUI subsystem");
			cegui_subsystem = subsystem_factory->createSubsystem(CEGuiRendererType::OGRE);
			
			LOG_INFO(logger, "Initializing CEGUI subsystem");
			cegui_subsystem->init();
			
			return true;
		}

		bool CEGuiPlugin::shutdown () 
		{
			LOG_INFO(logger, "Shutting down CEGUI plugin");
		  
			LOG_INFO(logger, "Shutting down CEGUI subsystem");
			cegui_subsystem->shutdown();
			
			LOG_INFO(logger, "Destroying CEGUI subsystem");
			subsystem_factory->destroySubsystem(cegui_subsystem);
			
			return true;
		}

		bool CEGuiPlugin::uninstall () 
		{
			LOG_INFO(logger, "Destroying CEGUI factory");
			subsystem_factory.reset();
			
			LOG_INFO(logger, "Uninstalling CEGUI plugin");
		  
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
