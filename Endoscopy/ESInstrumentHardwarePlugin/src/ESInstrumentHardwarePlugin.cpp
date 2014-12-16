#include <stdafx.h>

#include <ESInstrumentHardwarePlugin.h>
#include <Plugins/PluginsManager.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{

		ESInstrumentHardwarePlugin::ESInstrumentHardwarePlugin(const char* name):
		Core::BasePlugin(name),
		logger(name, Core::LogSeverity::NONE),
		hardware_manager(logger)
		{
		}

		ESInstrumentHardwarePlugin::~ESInstrumentHardwarePlugin()
		{
		}

		bool ESInstrumentHardwarePlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
			LOG_INFO(logger, "Logger initialized");
			
			LOG_INFO(logger, "Installing endoscopic instruments hardware plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool ESInstrumentHardwarePlugin::init () 
		{
			LOG_INFO(logger, "Initializing endoscopic instruments hardware plugin");
			
			hardware_manager.init();

			return true;
		}

		bool ESInstrumentHardwarePlugin::shutdown () 
		{
			LOG_INFO(logger, "Shutting down endoscopic instruments hardware plugin");
		  
			hardware_manager.shutdown();
			
			return true;
		}

		bool ESInstrumentHardwarePlugin::uninstall () 
		{
			LOG_INFO(logger, "Uninstalling endoscopic instruments hardware plugin");
		  
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
