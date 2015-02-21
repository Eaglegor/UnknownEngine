#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <SDLWindowManagerPlugin.h>
#include <WindowEventsProcessor.h>
#include <SDLWindowManager.h>
#include <SDLWindowDesc.h>
#include <SDLWindowManagerDescriptorGetter.h>
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
			SDLWindowManagerDescriptorGetter descriptor_getter;
			wm_desc = desc.descriptor.apply_visitor(descriptor_getter);

			logger = CREATE_LOGGER(getName(), wm_desc.log_level);

			LOG_INFO(logger, "Logger initialized");
			
			LOG_INFO(logger, "Installing SDL plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool SDLWindowManagerPlugin::init () 
		{
			LOG_INFO(logger, "Initializing SDL plugin");

			Core::IComponent* update_frame_provider = Core::ComponentsManager::getSingleton()->findComponent("Engine.MainLoop");
			window_manager.reset ( new SDLWindowManager(std::string(getName()), engine_context, logger, update_frame_provider) );
			window_manager->init();

			window_manager->createWindow( wm_desc.window_desc );

			return true;
		}

		bool SDLWindowManagerPlugin::shutdown () 
		{
			LOG_INFO(logger, "Shutting down SDL plugin");
		  
			window_manager->shutdown();
			window_manager.reset();
			
			return true;
		}

		bool SDLWindowManagerPlugin::uninstall () 
		{
			LOG_INFO(logger, "Uninstalling SDL plugin");
		  
			RELEASE_LOGGER(logger);
			return true;
		}
		
	} /* namespace Graphics */
} /* namespace UnknownEngine */
