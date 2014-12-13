#include <stdafx.h>

#include <ESInstrumentAlgorithmsPlugin.h>
#include <Plugins/PluginsManager.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{

		ESInstrumentAlgorithmsPlugin::ESInstrumentAlgorithmsPlugin(const char* name):
		Core::BasePlugin(name),
		logger(name, Core::LogSeverity::NONE)
		{
		}

		ESInstrumentAlgorithmsPlugin::~ESInstrumentAlgorithmsPlugin()
		{
		}

		bool ESInstrumentAlgorithmsPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
			LOG_INFO(logger, "Installing endoscopic instrument algorithms plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool ESInstrumentAlgorithmsPlugin::init () 
		{
			LOG_INFO(logger, "Initializing endoscopic instrument algorithms plugin");

			return true;
		}

		bool ESInstrumentAlgorithmsPlugin::shutdown () 
		{
			LOG_INFO(logger, "Shutting down endoscopic instrument algorithms plugin");
		  
			return true;
		}

		bool ESInstrumentAlgorithmsPlugin::uninstall () 
		{
			LOG_INFO(logger, "Uninstalling endoscopic instrument algorithms plugin");
		  
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
