#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <PhysXSubsystemPlugin.h>
#include <MessageSystem/MessageDictionary.h>
#include <EngineContext.h>
#include <LogHelper.h>
#include <PhysXSubsystem.h>

namespace UnknownEngine
{
	namespace Physics
	{

		PhysXSubsystemPlugin::PhysXSubsystemPlugin ()
		{
		}

		PhysXSubsystemPlugin::~PhysXSubsystemPlugin ()
		{
		}

		bool PhysXSubsystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
		  
			log_helper.reset(new Core::LogHelper(getName(), Core::LogMessage::Severity::LOG_SEVERITY_INFO, plugins_manager->getEngineContext()));
		  
			LOG_INFO(log_helper, "Logger initialized");
			
			LOG_INFO(log_helper, "Installing PhysX plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool PhysXSubsystemPlugin::init () 
		{
			LOG_INFO(log_helper, "Initializing PhysX plugin")

			physx_subsystem.reset(new PhysXSubsystem(engine_context, log_helper.get()));

			return true;
		}

		bool PhysXSubsystemPlugin::shutdown () 
		{
			LOG_INFO(log_helper, "Shutting down PhysX plugin");
		  
			physx_subsystem.reset();

			return true;
		}

		bool PhysXSubsystemPlugin::uninstall () 
		{
			LOG_INFO(log_helper, "Uninstalling PhysX plugin");
		  
			log_helper.reset();
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
