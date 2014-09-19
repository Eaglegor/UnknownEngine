#include <SDLWindowManager.h>
#include <SDLWindowDesc.h>
#include <WindowEventsProcessor.h>
#include <SDL.h>
#include <LogHelper.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/RenderSystem/GetWindowHandleMessage.h>
#include <Listeners/BaseMessageListenerBufferRegistrator.h>
#include <Listeners/BaseMessageListenersFactory.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <SDL_syswm.h>

namespace UnknownEngine
{
	namespace GUI
	{

		SDLWindowManager::SDLWindowManager ( const std::string& name, Core::EngineContext* engine_context, Core::LogHelper* log_helper ):
		engine_context(engine_context),
		log_helper(log_helper),
		name(name)
		{
			initSDL();
		}

		SDLWindowManager::~SDLWindowManager()
		{
			shutdownSDL();
		}
		
		void SDLWindowManager::onUpdateFrame(const Core::UpdateFrameMessage& msg)
		{
			window_events_listener->processEvents();
		}
		
		void SDLWindowManager::createWindow ( const SDLWindowDesc& desc )
		{
			size_t flags = SDL_WINDOW_SHOWN;
			if(desc.resizable) flags |= SDL_WINDOW_RESIZABLE;
			if(desc.full_screen) flags |= SDL_WINDOW_FULLSCREEN;
			
			sdl_windows.emplace( desc.window_name, SDL_CreateWindow(desc.window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, desc.width, desc.height, flags) );
			window_names.push_back(desc.window_name);
		}
		
		void SDLWindowManager::initSDL()
		{
			SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
			int result = SDL_Init( SDL_INIT_VIDEO );
			
			if(result < 0) 
			{
				LOG_ERROR(log_helper, "SDL initialization failed");
			}
			else
			{
				LOG_INFO(log_helper, "SDL initialized successfully");
			}
			
		}
		
		void SDLWindowManager::shutdownSDL()
		{
			
			LOG_INFO(log_helper, "Shutting down SDL");
			SDL_Quit();
			
			LOG_INFO(log_helper, "SDL shut down successfully");
		}
		
		void SDLWindowManager::getWindowHandle ( const Graphics::GetWindowHandleMessage& msg )
		{
			
			SDL_Window* window = getWindow(msg.requested_window_name);
			
			if(window != nullptr)
			{
				SDL_SysWMinfo info;
				SDL_VERSION(&info.version);
				
				if(SDL_GetWindowWMInfo(window, &info))
				{
	#ifdef _MSC_VER
					Graphics::NativeWindowHandleType handle = info.win.window;
	#else
					Graphics::NativeWindowHandleType handle = info.info.x11.window;
	#endif
					msg.result_callback(handle);
				}
				else
				{
					LOG_ERROR(log_helper, "Failed to retrieve window handle");
				}
			}
			
		}

		void SDLWindowManager::init(const Core::ReceivedMessageDescriptorsList &received_messages_desc)
		{
			window_events_listener.reset ( new WindowEventsProcessor(name, this, engine_context) );
			
			listener = std::move(
				Utils::BaseMessageListenersFactory::createBaseMessageListener(
					name  + ".Listener",
					engine_context,
					received_messages_desc
				) 
			);
			
			Utils::StandardMessageBuffersFactory<SDLWindowManager> factory(this);
			
			{
				typedef Core::UpdateFrameMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
				
				BufferType buffer = factory.createBuffer<BufferType>(&SDLWindowManager::onUpdateFrame);
				listener->registerMessageBuffer(buffer);
			}

			{
				typedef Graphics::GetWindowHandleMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
				
				BufferType buffer = factory.createBuffer<BufferType>(&SDLWindowManager::getWindowHandle);
				listener->registerMessageBuffer(buffer);
			}
			
			listener->registerAtDispatcher();
		}

		void SDLWindowManager::shutdown()
		{
			listener->unregisterAtDispatcher();
		}
		
		SDL_Window* SDLWindowManager::getWindow ( const std::string& name )
		{
			auto iter = sdl_windows.find(name);
			if(iter == sdl_windows.end()) return nullptr;
			else return iter->second;
		}

		std::string SDLWindowManager::getWindowName ( size_t window_id )
		{
			if(window_id > 0 && window_id <= window_names.size())
			{
				return window_names[window_id - 1];
			}
			throw WindowNotFound("Can't get window name for window id " + std::to_string(window_id));
		}
		
	}
}