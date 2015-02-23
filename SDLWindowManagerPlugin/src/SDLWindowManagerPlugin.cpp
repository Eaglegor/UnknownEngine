#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SDLWindowManagerPlugin.h>
#include <WindowEventsProcessor.h>
#include <SDLWindowManager.h>
#include <SDLWindowDesc.h>
#include <SDLWindowManagerDescriptorGetter.h>
#include <SDLWindowManagerFactory.h>
#include <MessageSystem/MessageDictionary.h>
#include <EngineContext.h>
#include <Logging.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <ExportedMessages/RenderSystem/GetWindowHandleMessage.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <boost/lexical_cast.hpp>

namespace UnknownEngine
{
	namespace GUI
	{

		SDLWindowManagerPlugin::SDLWindowManagerPlugin ( const char* name ):
		Core::BasePlugin(name),
		logger(nullptr)
		{
		}

		SDLWindowManagerPlugin::~SDLWindowManagerPlugin ()
		{
		}

		bool SDLWindowManagerPlugin::install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)
		{
			logger = CREATE_LOGGER(getName(), Core::LogSeverity::WARNING);
			
			LOG_INFO(logger, "Creating and registering SDL window manager factory");
			sdl_window_manager_factory.reset(new SDLWindowManagerFactory());
			Core::ComponentsManager::getSingleton()->addComponentFactory(sdl_window_manager_factory.get());
			
			LOG_INFO(logger, "SDL window manager plugin installed");
			
			return true;
		}

		bool SDLWindowManagerPlugin::init () 
		{
			return true;
		}

		bool SDLWindowManagerPlugin::shutdown () 
		{
			return true;
		}

		bool SDLWindowManagerPlugin::uninstall () 
		{
			LOG_INFO(logger, "Uninstalling SDL window manager plugin");
			LOG_INFO(logger, "Unregistering SDL window manager factory");
			Core::ComponentsManager::getSingleton()->removeComponentFactory(sdl_window_manager_factory.get());
			sdl_window_manager_factory.reset();
			
			RELEASE_LOGGER(logger);
			return true;
		}
		
	} /* namespace Graphics */
} /* namespace UnknownEngine */
