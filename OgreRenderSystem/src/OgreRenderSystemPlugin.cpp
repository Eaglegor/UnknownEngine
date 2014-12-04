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

#include <Factories/OgreGetDescriptorVisitor.h>

#include <Factories/OgreRenderableComponentsFactory.h>
#include <Factories/OgreCameraComponentsFactory.h>
#include <Factories/OgreLightComponentsFactory.h>
#include <Factories/OgreMeshPtrDataProvidersFactory.h>

#include <Parsers/Descriptors/OgreSubsystemDescParser.h>

#include <LogHelper.h>

#include <Objects/Entity.h>
#include <Objects/IComponent.h>
#include <ResourceManager.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderSystemPlugin::OgreRenderSystemPlugin () :
			engine_context ( nullptr ),
			renderable_components_factory ( nullptr ),
			camera_components_factory ( nullptr ),
			log_helper ( nullptr )
		{
		}

		OgreRenderSystemPlugin::~OgreRenderSystemPlugin ()
		{
			// TODO Auto-generated destructor stub
		}

		bool OgreRenderSystemPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc &desc )
		{

			this->desc = desc;
			this->engine_context = plugins_manager->getEngineContext();

			OgreGetDescriptorVisitor<OgreRenderSubsystemDescriptor, OgreRenderSubsystemDescriptorParser> descriptor_getter;
			OgreRenderSubsystemDescriptor render_system_desc = desc.descriptor.apply_visitor ( descriptor_getter );

			if (render_system_desc.log_level > Utils::LogSeverity::NONE)
			{
				log_helper.reset(new Utils::LogHelper(getName(), render_system_desc.log_level, engine_context));
			}

			LOG_INFO ( log_helper, "Logger started" );

			LOG_INFO ( log_helper, "Installing OGRE render subsystem" );

			LOG_INFO ( log_helper, "Registering new message type name: " + std::string ( ChangeMaterialActionMessage::getTypeName() ) );

			Core::MessageType message_type = engine_context->getMessageDictionary()->registerNewMessageType ( ChangeMaterialActionMessage::getTypeName() );

			LOG_DEBUG ( log_helper, std::string ( ChangeMaterialActionMessage::getTypeName() ) + ": assigned id: " + boost::lexical_cast<std::string> ( message_type ) );

			LOG_INFO ( log_helper, "Creating OGRE rendering subsystem" );

			render_system.reset ( new OgreRenderSubsystem ( render_system_desc, log_helper.get(), engine_context ) );

			LOG_INFO ( log_helper, "Creating factory for renderable components" );
			renderable_components_factory.reset ( new OgreRenderableComponentsFactory ( render_system.get(), engine_context, log_helper.get() ) );

			LOG_INFO ( log_helper, "Registering factory for renderable components" );
			engine_context->getComponentsManager()->addComponentFactory ( renderable_components_factory.get() );

			LOG_INFO ( log_helper, "Creating factory for camera components" );
			camera_components_factory.reset ( new OgreCameraComponentsFactory ( render_system.get(), engine_context, log_helper.get() ) );

			LOG_INFO ( log_helper, "Registering factory for camera components" );
			engine_context->getComponentsManager()->addComponentFactory ( camera_components_factory.get() );

			LOG_INFO ( log_helper, "Creating factory for light components" );
			light_components_factory.reset ( new OgreLightComponentsFactory ( render_system.get(), engine_context, log_helper.get() ) );

			LOG_INFO ( log_helper, "Registering factory for light components" );
			engine_context->getComponentsManager()->addComponentFactory ( light_components_factory.get() );

			LOG_INFO ( log_helper, "Creating factory for Ogre::MeshPtr data providers" );
			mesh_ptr_data_providers_factory.reset ( new OgreMeshPtrDataProvidersFactory ( log_helper.get(), engine_context, render_system.get() ) );

			LOG_INFO ( log_helper, "Registering factory for Ogre::MeshPtr data providers" );
			engine_context->getResourceManager()->addDataProviderFactory ( mesh_ptr_data_providers_factory.get() );

			return true;
		}

		bool OgreRenderSystemPlugin::init ()
		{
			LOG_INFO ( log_helper, "Initializing OGRE render subsystem" );

			render_system->start(desc.name);

			LOG_INFO ( log_helper, "OGRE render system initialized" );

			return true;
		}

		bool OgreRenderSystemPlugin::shutdown ()
		{

			LOG_INFO ( log_helper, "Shutting down OGRE render subsystem" );

			render_system->stop();

			LOG_INFO ( log_helper, "OGRE render system is shut down" );

			return true;
		}

		bool OgreRenderSystemPlugin::uninstall ()
		{

			LOG_INFO ( log_helper, "Uninstalling subsystem OGRE render subsystem" );

			LOG_INFO ( log_helper, "Unregistering Ogre::MeshPtr data providers factory" );
			engine_context->getResourceManager()->removeDataProviderFactory ( mesh_ptr_data_providers_factory.get() );

			LOG_INFO ( log_helper, "Destroying Ogre::MeshPtr data providers factory" );
			mesh_ptr_data_providers_factory.reset();

			LOG_INFO ( log_helper, "Unregistering camera components factory" );
			engine_context->getComponentsManager()->removeComponentFactory ( camera_components_factory.get() );

			LOG_INFO ( log_helper, "Destroying camera components factory" );
			camera_components_factory.reset();

			LOG_INFO ( log_helper, "Unregistering renderable components factory" );
			engine_context->getComponentsManager()->removeComponentFactory ( renderable_components_factory.get() );

			LOG_INFO ( log_helper, "Destroying renderable components factory" );
			renderable_components_factory.reset();

			LOG_INFO ( log_helper, "Unregistering light components factory" );
			engine_context->getComponentsManager()->removeComponentFactory ( light_components_factory.get() );

			LOG_INFO ( log_helper, "Destroying light components factory" );
			light_components_factory.reset();

			LOG_INFO ( log_helper, "Destroying subsystem object" );

			render_system.reset();

			LOG_INFO ( log_helper, "Subsystem uninstallation done" );

			log_helper.reset();

			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
