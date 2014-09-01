#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SimpleBehaviorPlugin.h>
#include <MessageSystem/MessageDictionary.h>
#include <ComponentsManager.h>
#include <EngineContext.h>
#include <LogHelper.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/StopEngineActionMessage.h>
#include <SimpleBehaviorsFactory.h>
#include <SimpleBehaviorUpdateFrameListener.h>
#include <SimpleBehaviorsPerformer.h>

#include <MessageSystem/BaseMessageListener.h>
#include <MessageSystem/MessageSender.h>
#include <Listeners/BaseMessageListenersFactory.h>
#include <Listeners/BaseMessageListenerBufferRegistrator.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <../UserInput/include/ExportedMessages/UserInput/KeyStateChangedMessage.h>

namespace UnknownEngine
{
	namespace Behavior
	{

		SimpleBehaviorPlugin::SimpleBehaviorPlugin ()
		{
		}

		SimpleBehaviorPlugin::~SimpleBehaviorPlugin ()
		{
		}

		bool SimpleBehaviorPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
		  
			log_helper.reset ( new Core::LogHelper(getName(), Core::LogMessage::Severity::LOG_SEVERITY_INFO, plugins_manager->getEngineContext()) );
		  
			LOG_INFO(log_helper, "Logger initialized");
			
			LOG_INFO(log_helper, "Installing simple behavior plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool SimpleBehaviorPlugin::init () 
		{
			LOG_INFO(log_helper, "Initializing simple behavior plugin")

			LOG_INFO ( log_helper, "Registering update frame listener..." );

			behaviors_performer.reset (new SimpleBehaviorsPerformer());


			stop_engine_message_sender.reset ( new Core::MessageSender<Core::StopEngineActionMessage>(
				Core::MessageSystemParticipantId("SimpleBehaviorPlugin", Core::MessageSystemParticipantId::AutoRegistrationPolicy::AUTO_REGISTER),
				engine_context
			) );
			
			listener = std::move(
				Utils::BaseMessageListenersFactory::createBaseMessageListener(
					"SimpleBehaviorPlugin.Listeners.UpdateFrameListener",
					engine_context,
					desc.received_messages
				) 
			);
			
			Utils::BaseMessageListenerBufferRegistrator<SimpleBehaviorPlugin> registrator(listener.get(), this);
			
			registrator.registerStandardMessageBuffer<
			Core::UpdateFrameMessage, 
			Utils::InstantForwardMessageBuffer<Core::UpdateFrameMessage>
			>( &SimpleBehaviorPlugin::onUpdateFrame );

			registrator.registerStandardMessageBuffer<
			IO::KeyStateChangedMessage, 
			Utils::InstantForwardMessageBuffer<IO::KeyStateChangedMessage>
			>( &SimpleBehaviorPlugin::onKeyPressed );
			
			listener->registerAtDispatcher();
			
			if(!simple_behaviors_factory) simple_behaviors_factory.reset( new SimpleBehaviorsFactory(engine_context, behaviors_performer.get()) );
			engine_context->getComponentsManager()->addComponentFactory(simple_behaviors_factory.get());
			
			return true;
		}

		bool SimpleBehaviorPlugin::shutdown () 
		{
			LOG_INFO(log_helper, "Shutting down simple behavior plugin");
		  
			engine_context->getComponentsManager()->removeComponentFactory(simple_behaviors_factory.get());
			
			listener->unregisterAtDispatcher();
			
			return true;
		}

		bool SimpleBehaviorPlugin::uninstall () 
		{
			LOG_INFO(log_helper, "Uninstalling simple behavior plugin");

			return true;
		}

		void SimpleBehaviorPlugin::onUpdateFrame( const Core::UpdateFrameMessage& msg )
		{
			behaviors_performer->perform();
		}

		void SimpleBehaviorPlugin::onKeyPressed ( const IO::KeyStateChangedMessage& msg )
		{
			if(msg.key == IO::Key::ESCAPE && msg.new_state == IO::KeyState::KEY_PRESSED)
			{
				Core::StopEngineActionMessage msg;
				stop_engine_message_sender->sendMessage(msg);
			}
		}
		
	} /* namespace Graphics */
} /* namespace UnknownEngine */
