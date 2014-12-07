#include <stdafx.h>

#include <boost/lexical_cast.hpp>

#include <ComponentSystem/ComponentDesc.h>

#include <Plugins/PluginsManager.h>
#include <OgreRenderSystemPlugin.h>
#include <MessageSystem/MessageDispatcher.h>

#include <ExportedMessages/UpdateFrameMessage.h>
#include <ExportedMessages/RenderSystem/ChangeMaterialActionMessage.h>
#include <Properties/Properties.h>
#include <EngineContext.h>
#include <OgreRenderSubsystem.h>

#include <ComponentSystem/ComponentsManager.h>

#include <Factories/OgreGetDescriptorVisitor.h>

#include <Factories/OgreRenderableComponentsFactory.h>
#include <Factories/OgreCameraComponentsFactory.h>
#include <Factories/OgreLightComponentsFactory.h>
#include <Factories/OgreMeshPtrDataProvidersFactory.h>

#include <Parsers/Descriptors/OgreSubsystemDescParser.h>

#include <Logging.h>

#include <ComponentSystem/Entity.h>
#include <ComponentSystem/IComponent.h>
#include <ResourceManager.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderSystemPlugin::OgreRenderSystemPlugin () :
			engine_context ( nullptr ),
			renderable_components_factory ( nullptr ),
			camera_components_factory ( nullptr ),
			logger ( nullptr )
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

			logger = CREATE_LOGGER(getName(), render_system_desc.log_level);

			LOG_INFO ( logger, "Logger started" );

			LOG_INFO ( logger, "Installing OGRE render subsystem" );

			LOG_INFO ( logger, "Creating OGRE rendering subsystem" );

			render_system.reset ( new OgreRenderSubsystem ( render_system_desc, logger, engine_context ) );

			LOG_INFO ( logger, "Creating factory for renderable components" );
			renderable_components_factory.reset ( new OgreRenderableComponentsFactory ( render_system.get(), engine_context, logger ) );

			LOG_INFO ( logger, "Registering factory for renderable components" );
			engine_context->getComponentsManager()->addComponentFactory ( renderable_components_factory.get() );

			LOG_INFO ( logger, "Creating factory for camera components" );
			camera_components_factory.reset ( new OgreCameraComponentsFactory ( render_system.get(), engine_context, logger ) );

			LOG_INFO ( logger, "Registering factory for camera components" );
			engine_context->getComponentsManager()->addComponentFactory ( camera_components_factory.get() );

			LOG_INFO ( logger, "Creating factory for light components" );
			light_components_factory.reset ( new OgreLightComponentsFactory ( render_system.get(), engine_context, logger ) );

			LOG_INFO ( logger, "Registering factory for light components" );
			engine_context->getComponentsManager()->addComponentFactory ( light_components_factory.get() );

			LOG_INFO ( logger, "Creating factory for Ogre::MeshPtr data providers" );
			mesh_ptr_data_providers_factory.reset ( new OgreMeshPtrDataProvidersFactory ( logger, engine_context, render_system.get() ) );

			LOG_INFO ( logger, "Registering factory for Ogre::MeshPtr data providers" );
			engine_context->getResourceManager()->addDataProviderFactory ( mesh_ptr_data_providers_factory.get() );

			return true;
		}

		bool OgreRenderSystemPlugin::init ()
		{
			LOG_INFO ( logger, "Initializing OGRE render subsystem" );

			render_system->start(desc.name);

			LOG_INFO ( logger, "OGRE render system initialized" );

			return true;
		}

		bool OgreRenderSystemPlugin::shutdown ()
		{

			LOG_INFO ( logger, "Shutting down OGRE render subsystem" );

			render_system->stop();

			LOG_INFO ( logger, "OGRE render system is shut down" );

			return true;
		}

		bool OgreRenderSystemPlugin::uninstall ()
		{

			LOG_INFO ( logger, "Uninstalling subsystem OGRE render subsystem" );

			LOG_INFO ( logger, "Unregistering Ogre::MeshPtr data providers factory" );
			engine_context->getResourceManager()->removeDataProviderFactory ( mesh_ptr_data_providers_factory.get() );

			LOG_INFO ( logger, "Destroying Ogre::MeshPtr data providers factory" );
			mesh_ptr_data_providers_factory.reset();

			LOG_INFO ( logger, "Unregistering camera components factory" );
			engine_context->getComponentsManager()->removeComponentFactory ( camera_components_factory.get() );

			LOG_INFO ( logger, "Destroying camera components factory" );
			camera_components_factory.reset();

			LOG_INFO ( logger, "Unregistering renderable components factory" );
			engine_context->getComponentsManager()->removeComponentFactory ( renderable_components_factory.get() );

			LOG_INFO ( logger, "Destroying renderable components factory" );
			renderable_components_factory.reset();

			LOG_INFO ( logger, "Unregistering light components factory" );
			engine_context->getComponentsManager()->removeComponentFactory ( light_components_factory.get() );

			LOG_INFO ( logger, "Destroying light components factory" );
			light_components_factory.reset();

			LOG_INFO ( logger, "Destroying subsystem object" );

			render_system.reset();

			LOG_INFO ( logger, "Subsystem uninstallation done" );

			RELEASE_LOGGER(logger);

			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
