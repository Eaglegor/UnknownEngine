/*
 * Engine.cpp
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <Engine.h>
#include <MainLoop/MainLoop.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageSystemParticipantDictionary.h>
#include <MessageSystem/MessageSender.h>
#include <ResourceManager.h>
#include <Plugins/PluginsManager.h>
#include <ComponentsManager.h>

#include <ExportedMessages/LogMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>

#include <SubsystemDesc.h>
#include <ISceneLoader.h>

#include <StopEngineListener.h>

#define ENABLE_CORE_SUBSYSTEM_INFO_LOG
#include <CoreLogging.h>
#include <ExportedMessages/TransformChangedMessage.h>

namespace UnknownEngine
{
	namespace Core
	{

		Engine::Engine() :
			state ( CREATED )
		{
			CORE_SUBSYSTEM_INFO ( "Engine created" );
		}

		Engine::~Engine()
		{
		}

		void Engine::start() 
		{

			CORE_SUBSYSTEM_INFO ( "Starting engine" );

			if ( state == CREATED ) throw InvalidEngineStateException ( "Engine wasn't initialized. Please call Engine::init() prior to Engine::start()" );
			if ( state == STARTED ) throw InvalidEngineStateException ( "Can't start the engine twice" );

			state = STARTED;

			MainLoop main_loop(&context);

			CORE_SUBSYSTEM_INFO ( "Registering engine stop listener" );
			StopEngineListener stop_listener ( "Engine.EngineStopListener", &main_loop );
			
			initListenerRules(stop_listener.getMessageSystemParticipantId());
			
			context.getMessageDispatcher()->addListener ( MESSAGE_TYPE_ID(StopEngineActionMessage::getTypeName()), &stop_listener );

			CORE_SUBSYSTEM_INFO ( "Starting main loop" );
			main_loop.start();

			CORE_SUBSYSTEM_INFO ( "Unregistering engine stop listener" );
			context.getMessageDispatcher()->removeListener ( &stop_listener );

			state = STOPPED;

		}

		void Engine::stop()
		{
			CORE_SUBSYSTEM_INFO ( "Stopping engine" );
			MessageSender<StopEngineActionMessage> sender("Engine.Stopper", &context);
			sender.sendMessage(StopEngineActionMessage());
		}
		
		void Engine::shutdown() 
		{

			CORE_SUBSYSTEM_INFO ( "Shutting down engine" );

			if ( state == STARTED ) throw InvalidEngineStateException ( "Shutting down running engine is not allowed" );
			if ( state == CREATED ) throw InvalidEngineStateException ( "Shutting down uninitialized engine is not allowed" );

			CORE_SUBSYSTEM_INFO ( "Destroying remaining entities" );
			this->context.components_manager->clearEntities();

			this->context.resource_manager->cleanup();
			
			CORE_SUBSYSTEM_INFO ( "Destroying plugins manager" );
			PluginsManager::destroyInstance();

			CORE_SUBSYSTEM_INFO ( "Destroying components manager" );
			ComponentsManager::destroyInstance();

			CORE_SUBSYSTEM_INFO ( "Destroying message system participant dictionary" );
			MessageSystemParticipantDictionary::destroyInstance();

			CORE_SUBSYSTEM_INFO ( "Destroying resource manager" );
			ResourceManager::destroyInstance();

			CORE_SUBSYSTEM_INFO ( "Destroying message dispatcher" );
			MessageDispatcher::destroyInstance();

			CORE_SUBSYSTEM_INFO ( "Destroying message dictionary" );
			MessageDictionary::destroyInstance();

			CORE_SUBSYSTEM_INFO ( "Engine shutdown complete" );

			state = CREATED;
		}

		EngineContext& Engine::getContext()
		{
			return context;
		}

		void Engine::init() 
		{

			CORE_SUBSYSTEM_INFO ( "Initializing engine" );

			if ( state == INIT ) throw InvalidEngineStateException ( "Double engine initialization is not allowed" );
			if ( state == STARTED ) throw InvalidEngineStateException ( "Running engine initialization is not allowed" );
			if ( state == STOPPED ) throw InvalidEngineStateException ( "Stopped engine initialization is not allowed. Call shutdown() prior." );

			CORE_SUBSYSTEM_INFO ( "Creating message dictionary" );
			context.message_dictionary = MessageDictionary::createInstance();

			CORE_SUBSYSTEM_INFO ( "Creating message dispatcher" );
			context.message_dispatcher = MessageDispatcher::createInstance();

			CORE_SUBSYSTEM_INFO ( "Creating components manager" );
			context.components_manager = ComponentsManager::createInstance();

			CORE_SUBSYSTEM_INFO ( "Creating resource manager" );
			context.resource_manager = ResourceManager::createInstance();

			CORE_SUBSYSTEM_INFO ( "Creating message participant dictionary" );
			context.message_system_participant_dictionary = MessageSystemParticipantDictionary::createInstance();

			CORE_SUBSYSTEM_INFO ( "Creating plugins manager" );
			plugins_manager = PluginsManager::createInstance ( &context );

			CORE_SUBSYSTEM_INFO ( "Creating engine message system participant id" );
			message_system_participant_id.name = "Engine";
			message_system_participant_id.id = context.message_system_participant_dictionary->registerNewMessageParticipant ( "Engine" );

			CORE_SUBSYSTEM_INFO ( "Registering internal message types" );
			registerInternalMessageTypes();

			state = INIT;
		}

		void Engine::registerInternalMessageTypes()
		{
			CORE_SUBSYSTEM_INFO ( "Registering message type: " + std::string ( Utils::LogMessage::getTypeName() ) );
			context.message_dictionary->registerNewMessageType ( Utils::LogMessage::getTypeName() );

			CORE_SUBSYSTEM_INFO ( "Registering message type: " + std::string ( UpdateFrameMessage::getTypeName() ) );
			context.message_dictionary->registerNewMessageType ( UpdateFrameMessage::getTypeName() );

			CORE_SUBSYSTEM_INFO ( "Registering message type: " + std::string ( TransformChangedMessage::getTypeName() ) );
			context.message_dictionary->registerNewMessageType ( TransformChangedMessage::getTypeName() );
			
			CORE_SUBSYSTEM_INFO ( "Registering message type: " + std::string ( StopEngineActionMessage::getTypeName() ) );
			context.message_dictionary->registerNewMessageType ( StopEngineActionMessage::getTypeName() );
		}

		PluginsManager* Engine::getPluginsManager()
		{
			return plugins_manager;
		}

		void Engine::initListenerRules(const MessageSystemParticipantId &message_system_participant)
		{
			MessageDispatcher::ListenerRulesDesc listener_rules;
			MessageDispatcher::ListenerRulesDesc::ReceivableMessageDesc msg;
			
			msg.message_type_name = StopEngineActionMessage::getTypeName();
			
			listener_rules.receivable_messages.push_back(msg);
			context.getMessageDispatcher()->setListenerRules(message_system_participant, listener_rules);
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
