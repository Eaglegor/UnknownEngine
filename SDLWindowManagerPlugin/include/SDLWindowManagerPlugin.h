#pragma once

#include <InlineSpecification.h>
#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>
#include <SDLWindowManagerDescriptor.h>

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
		class ILogger;
	}

	namespace GUI
	{

		class SDLWindowManager;

		class WindowEventsProcessor;

		class SDLWindowManagerPlugin: public Core::BasePlugin
		{
			public:
				SDLWindowManagerPlugin(const char* name);
				virtual ~SDLWindowManagerPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc) override;
				virtual bool init() override;
				virtual bool shutdown() override;
				virtual bool uninstall() override;

			private:
				SDLWindowManagerDescriptor wm_desc;
				std::unique_ptr<SDLWindowManager> window_manager;
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				Core::ILogger* logger;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
