#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <DummySubsystem.h>
#include <MessageSystem/MessageDictionary.h>
#include <EngineContext.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Dummy
	{

		DummySubsystemPlugin::DummySubsystemPlugin ()
		:logger(nullptr)
		{
		}

		DummySubsystemPlugin::~DummySubsystemPlugin ()
		{
		}

		bool DummySubsystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
		  
			logger = CREATE_LOGGER(getName(), Core::LogSeverity::INFO);
		  
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
		  
			RELEASE_LOGGER(logger);
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
