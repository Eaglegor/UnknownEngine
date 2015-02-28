#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SimpleBehaviorPlugin.h>
#include <MessageSystem/MessageDictionary.h>
#include <ComponentSystem/ComponentsManager.h>
#include <EngineContext.h>
#include <Logging.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/StopEngineActionMessage.h>
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <Factories/SimpleBehaviorsFactory.h>
#include <SimpleBehaviorsPerformer.h>

#include <MessageSystem/BaseMessageListener.h>
#include <MessageSystem/MessageSender.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>

#include <Parsers/SimpleBehaviorsPluginDescriptorGetter.h>

namespace UnknownEngine
{
	namespace Behavior
	{

		SimpleBehaviorPlugin::SimpleBehaviorPlugin ( const char* name ):
		Core::BasePlugin(name)
		{
		}

		SimpleBehaviorPlugin::~SimpleBehaviorPlugin ()
		{
		}

		bool SimpleBehaviorPlugin::install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)
		{
			SimpleBehaviorsPluginDescriptorGetter descriptor_getter;
			plugin_desc = desc.descriptor.apply_visitor(descriptor_getter);

			logger = CREATE_LOGGER(getName(), plugin_desc.log_level);
	  
			LOG_INFO(logger, "Logger initialized");
			
			LOG_INFO(logger, "Installing simple behavior plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool SimpleBehaviorPlugin::init () 
		{
			LOG_INFO(logger, "Initializing simple behavior plugin");

			LOG_INFO ( logger, "Registering update frame listener..." );

			if(!simple_behaviors_factory) simple_behaviors_factory.reset( new SimpleBehaviorsFactory() );
			engine_context->getComponentsManager()->addComponentFactory(simple_behaviors_factory.get());

			return true;
		}

		bool SimpleBehaviorPlugin::shutdown () 
		{
			LOG_INFO(logger, "Shutting down simple behavior plugin");

			engine_context->getComponentsManager()->removeComponentFactory(simple_behaviors_factory.get());
			
			return true;
		}

		bool SimpleBehaviorPlugin::uninstall () 
		{
			LOG_INFO(logger, "Uninstalling simple behavior plugin");

			RELEASE_LOGGER(logger);
			
			return true;
		}
		
	} /* namespace Graphics */
} /* namespace UnknownEngine */
