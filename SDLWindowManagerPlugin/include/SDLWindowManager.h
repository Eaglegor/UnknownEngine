#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <MessageSystem/MessageListenerDesc.h>
#include <Exception.h>

struct SDL_Window;

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class BaseMessageListener;
		class LogHelper;
		struct UpdateFrameMessage;
	}

	namespace Graphics
	{
		struct GetWindowHandleMessage;
	}
	
	namespace GUI
	{

		class WindowEventsProcessor;
		struct SDLWindowDesc;
		
		class SDLWindowManager
		{
		public:
			
			UNKNOWNENGINE_SIMPLE_EXCEPTION(WindowNotFound);
			
			SDLWindowManager(const std::string &name, Core::EngineContext* engine_context, Core::LogHelper* log_helper);
			virtual ~SDLWindowManager();
			
			void init( const Core::ReceivedMessageDescriptorsList& received_messages_desc );
			void shutdown();
			void createWindow(const SDLWindowDesc &desc);

			SDL_Window* getWindow(const std::string &name);
			std::string getWindowName(size_t window_id);
			
		private:
			void initSDL();
			void shutdownSDL();
			void onUpdateFrame(const Core::UpdateFrameMessage& msg);
			void getWindowHandle( const Graphics::GetWindowHandleMessage& msg );
			
			std::vector<std::string> window_names;
			
			std::unique_ptr< WindowEventsProcessor > window_events_listener;
			Core::EngineContext* engine_context;
			std::unique_ptr< Core::BaseMessageListener > listener;
			std::unordered_map<std::string, SDL_Window*> sdl_windows;
			Core::LogHelper* log_helper;
			std::string name;
		};
		
	}
}