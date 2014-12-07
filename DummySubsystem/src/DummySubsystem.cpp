#include <stdafx.h>

#include <DummySubsystem.h>
#include <Plugins/PluginsManager.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Dummy
	{

		DummySubsystemPlugin::DummySubsystemPlugin (const char* name):
		Core::BasePlugin(name),
		logger(name, Core::LogSeverity::NONE)
		{
		}

		DummySubsystemPlugin::~DummySubsystemPlugin ()
		{
		}

		bool DummySubsystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
			LOG_INFO(logger, "Logger initialized");
			
			LOG_INFO(logger, "Installing dummy plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool DummySubsystemPlugin::init () 
		{
			LOG_INFO(logger, "Initializing dummy plugin");

			return true;
		}

		bool DummySubsystemPlugin::shutdown () 
		{
			LOG_INFO(logger, "Shutting down dummy plugin");
		  
			return true;
		}

		bool DummySubsystemPlugin::uninstall () 
		{
			LOG_INFO(logger, "Uninstalling dummy plugin");
		  
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
