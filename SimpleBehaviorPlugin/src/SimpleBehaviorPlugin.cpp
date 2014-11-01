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
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <SimpleBehaviorsFactory.h>
#include <SimpleBehaviorsPerformer.h>

#include <MessageSystem/BaseMessageListener.h>
#include <MessageSystem/MessageSender.h>
#include <Listeners/BaseMessageListenersFactory.h>
#include <Listeners/StandardMessageBuffersFactory.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>

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
		  
			log_helper.reset ( new Utils::LogHelper(getName(), Utils::LogSeverity::INFO, plugins_manager->getEngineContext()) );
		  
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
				GET_OR_CREATE_MESSAGE_SYSTEM_PARTICIPANT_ID(std::string(getName())),
				engine_context
			) );
			
			listener = std::move(
				Utils::BaseMessageListenersFactory::createBaseMessageListener(
					"SimpleBehaviorPlugin.Listeners.UpdateFrameListener",
					engine_context,
					desc.received_messages
				) 
			);
			
			Utils::StandardMessageBuffersFactory<SimpleBehaviorPlugin> factory(this);
			
			{
				typedef Core::UpdateFrameMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;

				BufferType buffer = factory.createBuffer<BufferType>(&SimpleBehaviorPlugin::onUpdateFrame);
				listener->registerMessageBuffer(buffer);
			}
			
			Core::MessageSender<IO::AddSimpleActionMessage> add_action_sender(
				GET_OR_CREATE_MESSAGE_SYSTEM_PARTICIPANT_ID(std::string(getName())),
				engine_context
			);
			IO::AddSimpleActionMessage msg;
			msg.context_name = "Generic";
			msg.action_slot_name = "StopEngine";
			msg.action_callback = std::bind(&SimpleBehaviorPlugin::stopEngine, this);
			add_action_sender.sendMessage(msg);
			
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
			behaviors_performer->perform(msg.dt);
		}

		void SimpleBehaviorPlugin::stopEngine ( )
		{
			stop_engine_message_sender->sendMessage(Core::StopEngineActionMessage());
		}
		
	} /* namespace Graphics */
} /* namespace UnknownEngine */
