#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <AssimpMeshDataLoaderPlugin.h>
#include <Factories/AssimpMeshDataProvidersFactory.h>
#include <EngineContext.h>
#include <Logging.h>
#include <ResourceManager/ResourceManager.h>
#include <AssimpMeshDataLoaderDescriptor.h>
#include <Factories/AssimpResourceLoadersFactory.h>

namespace UnknownEngine
{
	namespace Loader
	{

		AssimpMeshDataLoaderPlugin::AssimpMeshDataLoaderPlugin ( const char* name ):
		Core::BasePlugin(name),
		logger(nullptr)
		{
		}

		AssimpMeshDataLoaderPlugin::~AssimpMeshDataLoaderPlugin ()
		{
		}

		bool AssimpMeshDataLoaderPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
		  
			//const Core::Properties& props = boost::get<Core::Properties>(desc.descriptor);
			AssimpMeshDataLoaderDescriptor descriptor;
			//descriptor = props;
			
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

			LOG_INFO(logger, "Creating Assimp mesh data loaders factory");
			resource_loaders_factory.reset( new AssimpResourceLoadersFactory(logger, engine_context) );
			
			Core::ResourceManager::getSingleton()->addResourceLoadersFactory(resource_loaders_factory.get());
			
			return true;
		}

		bool AssimpMeshDataLoaderPlugin::shutdown () 
		{
			LOG_INFO(logger, "Shutting down Assimp mesh data loader plugin");
		  
			LOG_INFO(logger, "Unregistering mesh data provider factory");
			Core::ResourceManager::getSingleton()->removeResourceLoadersFactory(resource_loaders_factory.get());
			
			LOG_INFO(logger, "Destroying Assimp mesh data provider factory");
			resource_loaders_factory.reset();
			
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
