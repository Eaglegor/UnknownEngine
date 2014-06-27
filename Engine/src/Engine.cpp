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

namespace UnknownEngine
{
	namespace Core
	{

		Engine::Engine() :
						message_dispatcher(new MessageDispatcher()),
						message_dictionary(new MessageDictionary()),
                        components_manager(new ComponentsManager()),
                        plugins_manager( new PluginsManager(components_manager, message_dispatcher, message_dictionary) )
        {
		}

		Engine::~Engine()
		{
			delete this->plugins_manager;
            delete this->components_manager;
			delete this->message_dictionary;
			delete this->message_dispatcher;
		}

		void Engine::start()
		{

			SubsystemDesc ssdesc;
			ssdesc.module_name = "libDirectX11RenderSystemPlugin.dll";

			plugins_manager->loadSubsystem(ssdesc);
			plugins_manager->initSubsystems();

			Graphics::CreateRenderWindowMessage msg;
			Graphics::RenderWindowDesc desc;
			desc.fullscreen = false;
			desc.width = 800;
			desc.height = 600;
			msg.window_desc = desc;

			this->message_dispatcher->deliverMessage(Graphics::CreateRenderWindowMessagePacker(SystemPartId("Engine")).packMessage(msg));

			MainLoop main_loop;
			main_loop.start();
		}

		void Engine::init()
		{
			message_dictionary->registerNewMessageType(LogMessage::getTypeName());
			message_dictionary->registerNewMessageType(UpdateFrameMessage::getTypeName());
		}

		void Engine::loadScene(const Loader::ISceneLoader* loader)
		{
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

                
                
                
                
        } /* namespace Core */
} /* namespace UnknownEngine */
