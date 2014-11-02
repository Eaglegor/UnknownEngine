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
		class BaseMessageListener;
		struct UpdateFrameMessage;
	}

	namespace Utils
	{
		class LogHelper;
	}
	
	namespace GUI
	{

		class SDLWindowManager;

		class WindowEventsProcessor;

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

				std::unique_ptr<SDLWindowManager> window_manager;
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				std::unique_ptr<Utils::LogHelper> log_helper;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
