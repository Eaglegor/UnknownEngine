#include <stdafx.h>

#include <CEGuiPlugin.h>
#include <CEGuiSubsystemFactory.h>
#include <Plugins/PluginsManager.h>
#include <Logging.h>
#include <MessageSystem/BaseMessageListener.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <ExportedMessages/SubsystemInitializedMessage.h>

namespace UnknownEngine
{
	namespace GUI
	{

		CEGuiPlugin::CEGuiPlugin(const char* name):
		Core::BasePlugin(name),
		logger(name, Core::LogSeverity::INFO),
		cegui_subsystem(nullptr),
		was_init(false)
		{
		}

		CEGuiPlugin::~CEGuiPlugin()
		{
		}

		bool CEGuiPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
			LOG_INFO(logger, "Logger initialized");
			
			LOG_INFO(logger, "Installing CEGUI plugin");

			LOG_INFO(logger, "Creating CEGUI factory");
			subsystem_factory.reset(new CEGuiSubsystemFactory(logger));
			
			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			listener.reset(new Core::BaseMessageListener(getName()));
			{
				typedef Utils::SubsystemInitializedMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
				
				listener->createMessageBuffer<MessageType, BufferType>(this, &CEGuiPlugin::onTargetSubsystemInitialized);
			}
			
			listener->registerAtDispatcher();
			
			return true;
		}

		bool CEGuiPlugin::init () 
		{
			return true;
		}

		bool CEGuiPlugin::shutdown () 
		{
			listener->unregisterAtDispatcher();
			
			if(!was_init) return true;
						   
			LOG_INFO(logger, "Shutting down CEGUI plugin");
		  
			LOG_INFO(logger, "Shutting down CEGUI subsystem");
			cegui_subsystem->shutdown();
			
			LOG_INFO(logger, "Destroying CEGUI subsystem");
			subsystem_factory->destroySubsystem(cegui_subsystem);
			
			was_init = false;
			return true;
		}

		bool CEGuiPlugin::uninstall () 
		{
			LOG_INFO(logger, "Destroying CEGUI factory");
			subsystem_factory.reset();
			
			LOG_INFO(logger, "Uninstalling CEGUI plugin");
		  
			return true;
		}

		void CEGuiPlugin::initImpl()
		{
			LOG_INFO(logger, "Initializing CEGUI plugin");

			LOG_INFO(logger, "Creating CEGUI subsystem");
			cegui_subsystem = subsystem_factory->createSubsystem(CEGuiRendererType::OGRE);
			
			LOG_INFO(logger, "Initializing CEGUI subsystem");
			cegui_subsystem->init();
			was_init = true;
		}

		void CEGuiPlugin::onTargetSubsystemInitialized ( const Utils::SubsystemInitializedMessage& msg )
		{
			initImpl();
		}
		
	} /* namespace Graphics */
} /* namespace UnknownEngine */
