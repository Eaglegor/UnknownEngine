#include <stdafx.h>

#include <EndoscopicInstrumentAlgorithmsPlugin.h>
#include <Plugins/PluginsManager.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{

		EndoscopicInstrumentAlgorithmsPlugin::EndoscopicInstrumentAlgorithmsPlugin(const char* name):
		Core::BasePlugin(name),
		logger(name, Core::LogSeverity::NONE)
		{
		}

		EndoscopicInstrumentAlgorithmsPlugin::~EndoscopicInstrumentAlgorithmsPlugin()
		{
		}

		bool EndoscopicInstrumentAlgorithmsPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
			LOG_INFO(logger, "Installing endoscopic instrument algorithms plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool EndoscopicInstrumentAlgorithmsPlugin::init () 
		{
			LOG_INFO(logger, "Initializing endoscopic instrument algorithms plugin");

			return true;
		}

		bool EndoscopicInstrumentAlgorithmsPlugin::shutdown () 
		{
			LOG_INFO(logger, "Shutting down endoscopic instrument algorithms plugin");
		  
			return true;
		}

		bool EndoscopicInstrumentAlgorithmsPlugin::uninstall () 
		{
			LOG_INFO(logger, "Uninstalling endoscopic instrument algorithms plugin");
		  
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
