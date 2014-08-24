#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SimpleBehaviorPlugin.h>
#include <MessageSystem/MessageDictionary.h>
#include <ComponentsManager.h>
#include <EngineContext.h>
#include <LogHelper.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <SimpleBehaviorsFactory.h>
#include <SimpleBehaviorUpdateFrameListener.h>

namespace UnknownEngine
{
	namespace Behavior
	{

		SimpleBehaviorPlugin::SimpleBehaviorPlugin ()
		:log_helper(nullptr),
		update_frame_listener(nullptr)
		{
		}

		SimpleBehaviorPlugin::~SimpleBehaviorPlugin ()
		{
		}

		bool SimpleBehaviorPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) throw ( Core::PluginError )
		{
		  
			log_helper = new Core::LogHelper(getName(), Core::LogMessage::Severity::LOG_SEVERITY_INFO, plugins_manager->getEngineContext());
		  
			LOG_INFO(log_helper, "Logger initialized");
			
			LOG_INFO(log_helper, "Installing simple behavior plugin");

			// Saving context for later use
			// Right now we don't know if all needed subsystems are already installed
			// That's why we do all init stuff in init() method
			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool SimpleBehaviorPlugin::init () throw ( Core::PluginError )
		{
			LOG_INFO(log_helper, "Initializing simple behavior plugin")

			LOG_INFO ( log_helper, "Registering update frame listener..." );
			update_frame_listener = new SimpleBehaviorUpdateFrameListener ("Behavior.SimpleBehaviorPlugin.Listeners.UpdateFrameListener");
			engine_context->getMessageDispatcher()->addListener ( Core::UpdateFrameMessage::getTypeName(), update_frame_listener );

			simple_behaviors_factory = new SimpleBehaviorsFactory(update_frame_listener, engine_context);
			engine_context->getComponentsManager()->addComponentFactory(simple_behaviors_factory);
			
			return true;
		}

		bool SimpleBehaviorPlugin::shutdown () throw ( Core::PluginError )
		{
			LOG_INFO(log_helper, "Shutting down simple behavior plugin");
		  
			engine_context->getComponentsManager()->removeComponentFactory(simple_behaviors_factory);
			delete simple_behaviors_factory;
			
			engine_context->getMessageDispatcher()->removeListener ( update_frame_listener );
			delete update_frame_listener;
			
			return true;
		}

		bool SimpleBehaviorPlugin::uninstall () throw ( Core::PluginError )
		{
			LOG_INFO(log_helper, "Uninstalling simple behavior plugin");

			if(log_helper) delete log_helper;
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
