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
#include <ResourceManager.h>
#include <Plugins/PluginsManager.h>
#include <ComponentsManager.h>

#include <ExportedMessages/LogMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>

#include <SubsystemDesc.h>
#include <ISceneLoader.h>

namespace UnknownEngine
{
	namespace Core
	{

		Engine::Engine() :
			state(CREATED)
        {
		}

		Engine::~Engine()
		{
		}

		void Engine::start() throw (InvalidEngineStateException)
		{

			if(state == CREATED) throw InvalidEngineStateException("Engine wasn't initialized. Please call Engine::init() prior to Engine::start()");
			if(state == STARTED) throw InvalidEngineStateException("Can't start the engine twice");

			state = STARTED;

			plugins_manager->initSubsystems();

			MainLoop main_loop;
			main_loop.start();

			state = STOPPED;

		}

		void Engine::shutdown() throw (InvalidEngineStateException)
		{

			if(state==STARTED) throw InvalidEngineStateException("Shutting down running engine is not allowed");
			if(state==CREATED) throw InvalidEngineStateException("Shutting down uninitialized engine is not allowed");

			delete this->plugins_manager;

			delete this->context.components_manager;
			delete this->context.message_dictionary;
			delete this->context.message_dispatcher;
			delete this->context.resource_manager;
			delete this->context.message_system_participant_dictionary;

			state = CREATED;
		}

		EngineContext& Engine::getContext()
		{
			return context;
		}

		void Engine::init() throw(InvalidEngineStateException)
		{
			if(state == INIT) throw InvalidEngineStateException("Twice engine initialization is not allowed");
			if(state == STARTED) throw InvalidEngineStateException("Running engine initialization is not allowed");
			if(state == STOPPED) throw InvalidEngineStateException("Stopped engine initialization is not allowed. Call shutdown() prior.");

			context.message_dictionary = new MessageDictionary();
			context.message_dispatcher = new MessageDispatcher();
			context.components_manager = new ComponentsManager();
			context.resource_manager = new ResourceManager();
			context.message_system_participant_dictionary = new MessageSystemParticipantDictionary();
			plugins_manager = new PluginsManager(&context);

			message_system_participant_id.name = "Engine";
			message_system_participant_id.id = context.message_system_participant_dictionary->registerNewMessageParticipant("Engine");

			registerInternalMessageTypes();

			state = INIT;
		}

		void Engine::loadScene(Loader::ISceneLoader* loader)
		{
			loader->loadScene(&context, plugins_manager);
        }

		void Engine::registerInternalMessageTypes()
		{
			context.message_dictionary->registerNewMessageType(LogMessage::getTypeName());
			context.message_dictionary->registerNewMessageType(UpdateFrameMessage::getTypeName());
		}

                
                
                
                
        } /* namespace Core */
} /* namespace UnknownEngine */
