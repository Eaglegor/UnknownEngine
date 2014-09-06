/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SDLWindowManagerPlugin.h>
#include <WindowEventsProcessor.h>
#include <SDLWindowManager.h>
#include <SDLWindowDesc.h>
#include <MessageSystem/MessageDictionary.h>
#include <EngineContext.h>
#include <LogHelper.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <Listeners/BaseMessageListenersFactory.h>
#include <Listeners/BaseMessageListenerBufferRegistrator.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <ExportedMessages/RenderSystem/GetWindowHandleMessage.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine
{
	namespace GUI
	{

		SDLWindowManagerPlugin::SDLWindowManagerPlugin ()
		:log_helper(nullptr)
		{
		}

		SDLWindowManagerPlugin::~SDLWindowManagerPlugin ()
		{
		}

		bool SDLWindowManagerPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
		  
			log_helper.reset( new Core::LogHelper(getName(), Core::LogMessage::Severity::LOG_SEVERITY_INFO, plugins_manager->getEngineContext()) );
		  
			LOG_INFO(log_helper, "Logger initialized");
			
			LOG_INFO(log_helper, "Installing SDL plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			engine_context->getMessageDictionary()->registerNewMessageType( IO::KeyStateChangedMessage::getTypeName() );
			engine_context->getMessageDictionary()->registerNewMessageType( Graphics::GetWindowHandleMessage::getTypeName() );
			engine_context->getMessageDictionary()->registerNewMessageType( Graphics::WindowResizedMessage::getTypeName() );
			
			return true;
		}

		bool SDLWindowManagerPlugin::init () 
		{
			LOG_INFO(log_helper, "Initializing SDL plugin")

			window_manager.reset ( new SDLWindowManager(std::string(getName()), engine_context, log_helper.get()) );
			window_manager->init(desc.received_messages);
			
			GUI::SDLWindowDesc window_desc;
			window_desc.full_screen = false;
			window_desc.resizable = true;
			window_desc.width = 640;
			window_desc.height = 480;
			window_desc.window_name="TestWindow";
			window_desc.window_title = "Hello!";
			
			window_manager->createWindow(window_desc);
			
			return true;
		}

		bool SDLWindowManagerPlugin::shutdown () 
		{
			LOG_INFO(log_helper, "Shutting down SDL plugin");
		  
			window_manager->shutdown();
			window_manager.reset();
			
			return true;
		}

		bool SDLWindowManagerPlugin::uninstall () 
		{
			LOG_INFO(log_helper, "Uninstalling SDL plugin");
		  
			log_helper.reset();
			return true;
		}
		
	} /* namespace Graphics */
} /* namespace UnknownEngine */
