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

		class WindowEventsProcessor;
		class SDLWindowManagerFactory;

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
				std::unique_ptr<SDLWindowManagerFactory> sdl_window_manager_factory;
				
				Core::SubsystemDesc desc;
				Core::ILogger* logger;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
