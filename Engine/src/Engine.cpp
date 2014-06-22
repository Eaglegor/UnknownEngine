/*
 * Engine.cpp
 *
 *  Created on: 22 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include "Engine.h"
#include <MainLoop/MainLoop.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageDictionary.h>
#include <Plugins/PluginsManager.h>
#include <ComponentManager.h>

#include <ExportedMessages/LogMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>

#include <ExportedMessages/RenderSystem/CreateRenderWindowMessage.h>

namespace UnknownEngine
{
	namespace Core
	{

		Engine::Engine() :
						message_dispatcher(new MessageDispatcher()),
						message_dictionary(new MessageDictionary()),
						component_manager(new ComponentManager()),
						plugins_manager(new PluginsManager())
		{
		}

		Engine::~Engine()
		{
			delete this->plugins_manager;
			delete this->component_manager;
			delete this->message_dictionary;
			delete this->message_dispatcher;
		}

		void Engine::start()
		{

			plugins_manager->loadModule("libDirectX11RenderSystemPlugin.dll");
			plugins_manager->initPlugins();

			Graphics::CreateRenderWindowMessage msg;
			Graphics::RenderWindowDesc desc;
			desc.fullscreen = false;
			desc.width = 800;
			desc.height = 600;
			msg.window_desc = desc;

			this->message_dispatcher->deliverMessage(Graphics::CreateRenderWindowMessagePacker(SenderInfo("Engine")).packMessage(msg));

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

	} /* namespace Core */
} /* namespace UnknownEngine */
