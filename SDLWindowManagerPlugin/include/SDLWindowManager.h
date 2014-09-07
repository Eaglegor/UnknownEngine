#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <MessageSystem/MessageListenerDesc.h>

class SDL_Window;

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class BaseMessageListener;
		class LogHelper;
		class UpdateFrameMessage;
	}

	namespace Graphics
	{
		class GetWindowHandleMessage;
	}
	
	namespace GUI
	{

		class WindowEventsProcessor;
		class SDLWindowDesc;
		
		class SDLWindowManager
		{
		public:
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
			
			size_t window_id_counter;
			
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