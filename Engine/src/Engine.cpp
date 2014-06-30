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
						message_dispatcher(new MessageDispatcher()),
						message_dictionary(new MessageDictionary()),
                        components_manager(new ComponentsManager()),
						plugins_manager( new PluginsManager(components_manager, message_dispatcher, message_dictionary) ),
						IMessageSystemParticipant( MessageSystemParticipantId("Engine") ),
						init_done(false)
        {
			registerInternalMessageTypes();
		}

		Engine::~Engine()
		{
			delete this->plugins_manager;
            delete this->components_manager;
			delete this->message_dictionary;
			delete this->message_dispatcher;
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

			this->message_dispatcher->deliverMessage(Graphics::CreateRenderWindowMessagePacker(MessageSystemParticipantId("Engine")).packMessage(msg));

			MainLoop main_loop;
			main_loop.start();
		}

		void Engine::init()
		{
			message_dictionary->registerNewMessageType(LogMessage::getTypeName());
			message_dictionary->registerNewMessageType(UpdateFrameMessage::getTypeName());
			init_done = true;
		}

		void Engine::loadScene(Loader::ISceneLoader* loader)
		{
			loader->loadScene(components_manager, plugins_manager);
        }

        MessageDispatcher *Engine::getMessageDispatcher() const
        {
            return message_dispatcher;
        }

        MessageDictionary *Engine::getMessageDictionary() const
        {
            return message_dictionary;
        }

        ComponentsManager *Engine::getComponentsManager() const
        {
			return components_manager;
		}

		void Engine::registerInternalMessageTypes()
		{
			message_dictionary->registerNewMessageType(LogMessage::getTypeName());
			message_dictionary->registerNewMessageType(UpdateFrameMessage::getTypeName());
		}

                
                
                
                
        } /* namespace Core */
} /* namespace UnknownEngine */
