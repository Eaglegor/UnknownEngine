#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <AssimpMeshDataLoaderPlugin.h>
#include <Factories/AssimpMeshDataProvidersFactory.h>
#include <AssimpMeshDataLoaderDescriptorGetter.h>
#include <EngineContext.h>
#include <Logging.h>
#include <ResourceManager/ResourceManager.h>

namespace UnknownEngine
{
	namespace Loader
	{

		AssimpMeshDataLoaderPlugin::AssimpMeshDataLoaderPlugin ()
		:logger(nullptr),
		data_provider_factory(nullptr)
		{
		}

		AssimpMeshDataLoaderPlugin::~AssimpMeshDataLoaderPlugin ()
		{
		}

		bool AssimpMeshDataLoaderPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
		  
			AssimpMeshDataLoaderDescriptorGetter descriptor_getter;
			AssimpMeshDataLoaderDescriptor descriptor = desc.descriptor.apply_visitor(descriptor_getter);
			
			logger = CREATE_LOGGER(getName(), descriptor.log_level);

			LOG_INFO(logger, "Logger initialized");
			
			LOG_INFO(logger, "Installing Assimp mesh data loader plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool AssimpMeshDataLoaderPlugin::init () 
		{
			
			LOG_INFO(logger, "Initializing Assimp mesh data loader plugin");

			LOG_INFO(logger, "Creating Assimp mesh data provider factory");
			data_provider_factory.reset( new AssimpMeshDataProvidersFactory(logger, engine_context) );
			
			LOG_INFO(logger, "Registering mesh data provider factory");
			engine_context->getResourceManager()->addDataProviderFactory(data_provider_factory.get());
			
			return true;
		}

		bool AssimpMeshDataLoaderPlugin::shutdown () 
		{
			LOG_INFO(logger, "Shutting down Assimp mesh data loader plugin");
		  
			LOG_INFO(logger, "Unregistering mesh data provider factory");
			engine_context->getResourceManager()->removeDataProviderFactory(data_provider_factory.get());
			
			LOG_INFO(logger, "Destroying Assimp mesh data provider factory");
			data_provider_factory.reset();
			
			return true;
		}

		bool AssimpMeshDataLoaderPlugin::uninstall () 
		{
			LOG_INFO(logger, "Uninstalling Assimp mesh data loader plugin");
		 
			RELEASE_LOGGER(logger);
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
