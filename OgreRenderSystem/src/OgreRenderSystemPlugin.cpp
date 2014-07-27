/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <OgreRenderSystemPlugin.h>
#include <MessageSystem/MessageDispatcher.h>

#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/RenderSystem/ChangeMaterialActionMessage.h>
#include <Properties/Properties.h>
#include <EngineContext.h>
#include <OgreRenderSubsystem.h>

#include <ComponentsManager.h>
#include <Factories/OgreRenderableComponentsFactory.h>
#include <Listeners/OgreUpdateFrameListener.h>
#include <Parsers/OgreSubsystemDescParser.h>

#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderSystemPlugin::OgreRenderSystemPlugin ()
		:log_helper(nullptr)
		{
		}

		OgreRenderSystemPlugin::~OgreRenderSystemPlugin ()
		{
			// TODO Auto-generated destructor stub
		}

		bool OgreRenderSystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc &desc ) throw ( Core::PluginError )
		{
		  
			setName(desc.name);
		  
			this->desc = desc;
			this->engine_context = plugins_manager->getEngineContext();
		  
			log_helper = new Core::LogHelper(getName(), Core::LogMessage::LOG_SEVERITY_INFO, engine_context);
		  
			LOG_INFO(log_helper, "Logger started");
			
			LOG_INFO(log_helper, "Installing OGRE render subsystem");

			LOG_INFO(log_helper, "Registering new message type name: " + std::string(ChangeMaterialActionMessage::getTypeName()) );
			
			engine_context->getMessageDictionary()->registerNewMessageType(ChangeMaterialActionMessage::getTypeName());
			
			LOG_INFO(log_helper, "Creating OGRE rendering subsystem");
			
			if(!desc.prepared_descriptor.isEmpty())
			{
				LOG_INFO(log_helper, "Predefined descriptor found");
				LOG_INFO(log_helper, "Creating subsystem object");
				
				render_system = new OgreRenderSubsystem(desc.prepared_descriptor.get<OgreRenderSubsystem::Descriptor>());
			}
			else
			{
				LOG_INFO(log_helper, "Predefined descriptor not found - string parser will be used");
				LOG_INFO(log_helper, "Creating subsystem object");
				
				render_system = new OgreRenderSubsystem(OgreRenderSubsystemDescriptorParser::parse(desc.creation_options));
			}
			
			LOG_INFO(log_helper, "Creating factory for component type 'Renderable'");
			
			renderable_components_factory = new OgreRenderableComponentsFactory(render_system, engine_context);

			LOG_INFO(log_helper, "Registering factory for component type 'Renderable'");
			
			engine_context->getComponentsManager()->addComponentFactory(renderable_components_factory);

			return true;
		}

		bool OgreRenderSystemPlugin::init () throw ( Core::PluginError )
		{
		  
			LOG_INFO(log_helper, "Initializing OGRE render subsystem");
		  
			LOG_INFO(log_helper, "Registering update frame listener...");
			
			update_frame_listener = new OgreUpdateFrameListener("Graphics.Ogre.Listeners.UpdateFrameListener", render_system);
			engine_context->getMessageDispatcher()->addListener(Core::UpdateFrameMessage::getTypeName(), update_frame_listener);
			

			return true;
		}

		bool OgreRenderSystemPlugin::shutdown () throw ( Core::PluginError )
		{
		  
			LOG_INFO(log_helper, "Shutting down OGRE render subsystem");
		  
			LOG_INFO(log_helper, "Unregistering update frame listener");

			engine_context->getMessageDispatcher()->removeListener(update_frame_listener);
			delete update_frame_listener;
			
			LOG_INFO(log_helper, "Update frame listener unregistered");
			
			return true;
		}

		bool OgreRenderSystemPlugin::uninstall () throw ( Core::PluginError )
		{

			LOG_INFO(log_helper, "Uninstalling subsystem OGRE render subsystem");
		  
			LOG_INFO(log_helper, "Unregistering component factory for type 'Renderable'" );
		  
			engine_context->getComponentsManager()->removeComponentFactory(renderable_components_factory);
			
			LOG_INFO(log_helper, "Destroying component factory for type 'Renderable'");
						       
			delete renderable_components_factory;
			
			LOG_INFO(log_helper, "Destroying subsystem object");
						       
			delete render_system;

			LOG_INFO(log_helper, "Subsystem uninstallation done");
		
			if(log_helper) delete log_helper;
			
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
