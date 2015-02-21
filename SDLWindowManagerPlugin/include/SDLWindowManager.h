#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <Exception.h>
#include <Scalar.h>
#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentSystem/IComponent.h>

struct SDL_Window;

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class BaseMessageListener;
		class ILogger;		
	}

	namespace Graphics
	{
		struct GetWindowHandleMessage;
	}
	
	namespace GUI
	{

		class WindowEventsProcessor;
		struct SDLWindowDesc;
		
		class SDLWindowManager : public ComponentInterfaces::UpdateFrameListenerComponent
		{
		public:
			
			UNKNOWNENGINE_SIMPLE_EXCEPTION(WindowNotFound);
			
			SDLWindowManager(const std::string &name, Core::EngineContext* engine_context, Core::ILogger* logger, Core::IComponent* update_frame_provider);
			virtual ~SDLWindowManager();
			
			void init();
			void shutdown();
			void createWindow(const SDLWindowDesc &desc);

			SDL_Window* getWindow(const std::string &name);
			std::string getWindowName(size_t window_id);
			
			void onUpdateFrame(Math::Scalar dt) override;
			
		private:
			void initSDL();
			void shutdownSDL();
			void getWindowHandle( const Graphics::GetWindowHandleMessage& msg );
			
			std::vector<std::string> window_names;
			
			std::unique_ptr< WindowEventsProcessor > window_events_listener;
			Core::EngineContext* engine_context;
			std::unique_ptr< Core::BaseMessageListener > listener;
			std::unordered_map<std::string, SDL_Window*> sdl_windows;
			Core::ILogger* logger;
			std::string name;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
		};
		
	}
}