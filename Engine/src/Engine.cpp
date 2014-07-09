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
#include <ResourceManager.h>
#include <Plugins/PluginsManager.h>
#include <ComponentsManager.h>

#include <ExportedMessages/LogMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>

#include <ExportedMessages/RenderSystem/CreateRenderWindowMessage.h>
#include <SubsystemDesc.h>
#include <ISceneLoader.h>

namespace UnknownEngine
{
	namespace Core
	{

		Engine::Engine() :
			init_done(false),
			IMessageSystemParticipant( MessageSystemParticipantId("Engine") )
        {
			registerInternalMessageTypes();
		}

		Engine::~Engine()
		{
			delete this->plugins_manager;

			delete this->context.components_manager;
			delete this->context.message_dictionary;
			delete this->context.message_dispatcher;
			delete this->context.resource_manager;

		}

		void Engine::start() throw (EngineNotInitializedException)
		{

			if(!init_done) throw EngineNotInitializedException("Engine wasn't initialized. Please call Engine::init() prior to Engine::start()");

			plugins_manager->initSubsystems();

			Graphics::CreateRenderWindowMessage msg;
			Graphics::RenderWindowDesc desc;
			desc.fullscreen = false;
			desc.width = 800;
			desc.height = 600;
			msg.window_desc = desc;

			context.message_dispatcher->deliverMessage(Graphics::CreateRenderWindowMessagePacker(MessageSystemParticipantId("Engine")).packMessage(msg));

			MainLoop main_loop;
			main_loop.start();
		}

		EngineContext& Engine::getContext()
		{
			return context;
		}

		void Engine::init()
		{
			if(init_done) throw EngineAlreadyInitializedException("Engine already initialized");
			context.message_dictionary = new MessageDictionary();
			context.message_dispatcher = new MessageDispatcher();
			context.components_manager = new ComponentsManager();
			context.resource_manager = new ResourceManager();
			plugins_manager = new PluginsManager(&context);

			context.message_dictionary->registerNewMessageType(LogMessage::getTypeName());
			context.message_dictionary->registerNewMessageType(UpdateFrameMessage::getTypeName());
			init_done = true;
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
