/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <boost/lexical_cast.hpp>

#include <ComponentDesc.h>

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
#include <Factories/OgreCameraComponentsFactory.h>
#include <Listeners/OgreUpdateFrameListener.h>
#include <Parsers/OgreSubsystemDescParser.h>

#include <LogHelper.h>

#include <Objects/Entity.h>
#include <Objects/Component.h>

#include <Components/OgreRenderableComponent.h>
#include <Components/OgreCameraComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderSystemPlugin::OgreRenderSystemPlugin ()
			: log_helper ( nullptr ),
			  renderable_components_factory ( nullptr ),
			  camera_components_factory ( nullptr ),
			  engine_context ( nullptr )
		{
		}

		OgreRenderSystemPlugin::~OgreRenderSystemPlugin ()
		{
			// TODO Auto-generated destructor stub
		}

		bool OgreRenderSystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc &desc ) throw ( Core::PluginError )
		{

			this->desc = desc;
			this->engine_context = plugins_manager->getEngineContext();

			boost::optional<const std::string&> log_level = desc.creation_options.get_optional<std::string> ( "log_level" );
			if ( log_level.is_initialized() )
			{
				log_helper = new Core::LogHelper ( getName(), Core::LogHelper::parseLogLevel ( log_level.get() ), engine_context );
			}

			LOG_INFO ( log_helper, "Logger started" );

			LOG_INFO ( log_helper, "Installing OGRE render subsystem" );

			LOG_INFO ( log_helper, "Registering new message type name: " + std::string ( ChangeMaterialActionMessage::getTypeName() ) );

			Core::MessageType message_type = engine_context->getMessageDictionary()->registerNewMessageType ( ChangeMaterialActionMessage::getTypeName() );

			LOG_DEBUG ( log_helper, std::string ( ChangeMaterialActionMessage::getTypeName() ) + ": assigned id: " + boost::lexical_cast<std::string> ( message_type ) );

			LOG_INFO ( log_helper, "Creating OGRE rendering subsystem" );

			if ( !desc.prepared_descriptor.isEmpty() )
			{
				LOG_INFO ( log_helper, "Predefined descriptor found" );
				LOG_INFO ( log_helper, "Creating subsystem object" );

				render_system = new OgreRenderSubsystem ( desc.prepared_descriptor.get<OgreRenderSubsystem::Descriptor>(), log_helper );
			}
			else
			{
				LOG_WARNING ( log_helper, "Predefined descriptor not found - string parser will be used" );
				LOG_INFO ( log_helper, "Creating subsystem object" );

				render_system = new OgreRenderSubsystem ( OgreRenderSubsystemDescriptorParser::parse ( desc.creation_options ), log_helper );
			}

			LOG_INFO ( log_helper, "Creating factory for component type 'Renderable'" );
			renderable_components_factory = new OgreRenderableComponentsFactory ( render_system, engine_context, log_helper );

			LOG_INFO ( log_helper, "Registering factory for component type 'Renderable'" );
			engine_context->getComponentsManager()->addComponentFactory ( renderable_components_factory );

			LOG_INFO ( log_helper, "Creating factory for component type 'Camera'" );
			camera_components_factory = new OgreCameraComponentsFactory ( render_system, engine_context, log_helper );

			LOG_INFO ( log_helper, "Registering factory for component type 'Camera'" );
			engine_context->getComponentsManager()->addComponentFactory ( camera_components_factory );

			return true;
		}

		bool OgreRenderSystemPlugin::init () throw ( Core::PluginError )
		{
			LOG_INFO ( log_helper, "Initializing OGRE render subsystem" );

			LOG_INFO ( log_helper, "Registering update frame listener..." );

			update_frame_listener = new OgreUpdateFrameListener ( "Graphics.Ogre.Listeners.UpdateFrameListener", render_system );
			engine_context->getMessageDispatcher()->addListener ( Core::UpdateFrameMessage::getTypeName(), update_frame_listener );

			LOG_INFO ( log_helper, "OGRE render system initialized" );

			return true;
		}

		bool OgreRenderSystemPlugin::shutdown () throw ( Core::PluginError )
		{

			LOG_INFO ( log_helper, "Shutting down OGRE render subsystem" );

			LOG_INFO ( log_helper, "Unregistering update frame listener" );

			engine_context->getMessageDispatcher()->removeListener ( update_frame_listener );
			delete update_frame_listener;

			LOG_INFO ( log_helper, "OGRE render system is shut down" );

			return true;
		}

		bool OgreRenderSystemPlugin::uninstall () throw ( Core::PluginError )
		{

			LOG_INFO ( log_helper, "Uninstalling subsystem OGRE render subsystem" );

			LOG_INFO ( log_helper, "Unregistering component factory for type 'Camera'" );
			engine_context->getComponentsManager()->removeComponentFactory ( camera_components_factory );

			LOG_INFO ( log_helper, "Destroying component factory for type 'Camera'" );
			delete camera_components_factory;

			LOG_INFO ( log_helper, "Unregistering component factory for type 'Renderable'" );
			engine_context->getComponentsManager()->removeComponentFactory ( renderable_components_factory );

			LOG_INFO ( log_helper, "Destroying component factory for type 'Renderable'" );
			delete renderable_components_factory;

			LOG_INFO ( log_helper, "Destroying subsystem object" );

			delete render_system;

			LOG_INFO ( log_helper, "Subsystem uninstallation done" );

			if ( log_helper ) delete log_helper;

			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
