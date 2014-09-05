#pragma once

/*
 * DirectX10RenderSystemPlugin.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <InlineSpecification.h>
#include <Plugins/Plugin.h>
#include <SubsystemDesc.h>

class SDL_Window;
namespace UnknownEngine
{
	namespace Graphics
	{

		struct GetWindowHandleMessage;
	}


	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
		class LogHelper;
		class BaseMessageListener;
		struct UpdateFrameMessage;
	}

	namespace IO
	{

		class WindowEventsListener;

		class SDLWindowManagerPlugin: public Core::Plugin
		{
			public:
				SDLWindowManagerPlugin();
				virtual ~SDLWindowManagerPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc) override;
				virtual bool init() override;
				virtual bool shutdown() override;
				virtual bool uninstall() override;

			private:
				void initSDL();
				void shutdownSDL();
				void onUpdateFrame(const Core::UpdateFrameMessage& msg);
				void getWindowHandle( const Graphics::GetWindowHandleMessage& msg );

				std::unique_ptr< WindowEventsListener > keyboard_listener;
				
				SDL_Window* sdl_window;
				
				std::unique_ptr< Core::BaseMessageListener > listener;
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				std::unique_ptr<Core::LogHelper> log_helper;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
