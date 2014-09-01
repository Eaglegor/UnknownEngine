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

		class KeyboardListener;

		class SDLUserInputPlugin: public Core::Plugin
		{
			public:
				SDLUserInputPlugin();
				virtual ~SDLUserInputPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc) override;
				virtual bool init() override;
				virtual bool shutdown() override;
				virtual bool uninstall() override;

			private:
				void initSDL();
				void shutdownSDL();
				void onUpdateFrame(const Core::UpdateFrameMessage& msg);

				std::unique_ptr< KeyboardListener > keyboard_listener;
				
				std::unique_ptr< Core::BaseMessageListener > listener;
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				std::unique_ptr<Core::LogHelper> log_helper;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
