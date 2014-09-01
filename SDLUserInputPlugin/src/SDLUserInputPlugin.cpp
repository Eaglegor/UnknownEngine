/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SDLUserInputPlugin.h>
#include <KeyboardListener.h>
#include <MessageSystem/MessageDictionary.h>
#include <EngineContext.h>
#include <LogHelper.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <Listeners/BaseMessageListenersFactory.h>
#include <Listeners/BaseMessageListenerBufferRegistrator.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <SDL.h>

namespace UnknownEngine
{
	namespace IO
	{

		SDLUserInputPlugin::SDLUserInputPlugin ()
		:log_helper(nullptr)
		{
		}

		SDLUserInputPlugin::~SDLUserInputPlugin ()
		{
		}

		bool SDLUserInputPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
		  
			log_helper.reset( new Core::LogHelper(getName(), Core::LogMessage::Severity::LOG_SEVERITY_INFO, plugins_manager->getEngineContext()) );
		  
			LOG_INFO(log_helper, "Logger initialized");
			
			LOG_INFO(log_helper, "Installing SDL plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			engine_context->getMessageDictionary()->registerNewMessageType( IO::KeyStateChangedMessage::getTypeName() );
			
			return true;
		}

		bool SDLUserInputPlugin::init () 
		{
			LOG_INFO(log_helper, "Initializing SDL plugin")

			initSDL();
			
			keyboard_listener.reset ( new KeyboardListener( std::string(getName()) +  ".KeyboardListener", engine_context) );
			
			listener = std::move(
				Utils::BaseMessageListenersFactory::createBaseMessageListener(
					std::string(getName())  + ".Listener",
					engine_context,
					desc.received_messages
				) 
			);
			
			Utils::BaseMessageListenerBufferRegistrator<SDLUserInputPlugin> registrator(listener.get(), this);
			
			registrator.registerStandardMessageBuffer<
			Core::UpdateFrameMessage, 
			Utils::InstantForwardMessageBuffer<Core::UpdateFrameMessage>
			>( &SDLUserInputPlugin::onUpdateFrame );
			
			listener->registerAtDispatcher();
			
			return true;
		}

		bool SDLUserInputPlugin::shutdown () 
		{
			LOG_INFO(log_helper, "Shutting down SDL plugin");
		  
			listener->unregisterAtDispatcher();
			
			shutdownSDL();
			
			return true;
		}

		bool SDLUserInputPlugin::uninstall () 
		{
			LOG_INFO(log_helper, "Uninstalling SDL plugin");
		  
			log_helper.reset();
			return true;
		}
		
		void SDLUserInputPlugin::onUpdateFrame(const Core::UpdateFrameMessage& msg)
		{
			keyboard_listener->processEvents();
		}
		
		void SDLUserInputPlugin::initSDL()
		{
			int result = SDL_Init( SDL_INIT_VIDEO );
			SDL_SetVideoMode(20,20,0,SDL_SWSURFACE | SDL_NOFRAME);
			SDL_WM_GrabInput(SDL_GRAB_ON);

			if(result < 0) {
				LOG_ERROR(log_helper, "Failed to initialize SDL");
			}
			else 
			{
				LOG_INFO(log_helper, "SDL initialized successfully");
			}
		}
		
		void SDLUserInputPlugin::shutdownSDL()
		{
			LOG_INFO(log_helper, "Grab off");
			SDL_WM_GrabInput(SDL_GRAB_OFF);
			
			LOG_INFO(log_helper, "Shutting down SDL");
			//SDL_Quit();
			
			LOG_INFO(log_helper, "SDL shut down successfully");
		}
		
	} /* namespace Graphics */
} /* namespace UnknownEngine */
