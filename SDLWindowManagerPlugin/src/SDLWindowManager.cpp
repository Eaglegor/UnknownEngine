#include <stdafx.h>
#include <SDLWindowManager.h>
#include <SDLWindowDesc.h>
#include <WindowEventsProcessor.h>
#include <SDL.h>
#include <Logging.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/RenderSystem/GetWindowHandleMessage.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <MessageSystem/BaseMessageListener.h>
#include <SDL_syswm.h>
#include <thread>

namespace UnknownEngine
{
	namespace GUI
	{

		SDLWindowManager::SDLWindowManager ( const std::string& name, const SDLWindowManagerDescriptor &desc):
		Core::BaseComponent(name.c_str()),
		desc(desc),
		logger(name.c_str(), desc.log_level),
		name(name)
		{
		}

		SDLWindowManager::~SDLWindowManager()
		{
		}

		bool SDLWindowManager::init()
		{
			SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
			int result = SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );
			
			if(result < 0) 
			{
				LOG_ERROR(logger, "SDL initialization failed");
				return false;
			}
			else
			{
				LOG_INFO(logger, "SDL initialized successfully");
				return true;
			}
		}

		void SDLWindowManager::shutdown()
		{
			LOG_INFO(logger, "Shutting down SDL");
			SDL_Quit();
			
			LOG_INFO(logger, "SDL shut down successfully");
		}
		
	}
}