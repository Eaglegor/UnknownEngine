/*
 * DirectX10RenderSystemPlugin.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <Plugins/PluginsManager.h>
#include <Properties/Properties.h>
#include <AssimpMeshDataLoaderPlugin.h>
#include <Factories/AssimpMeshDataProvidersFactory.h>
#include <EngineContext.h>
#include <LogHelper.h>
#include <ResourceManager.h>

namespace UnknownEngine
{
	namespace Loader
	{

		AssimpMeshDataLoaderPlugin::AssimpMeshDataLoaderPlugin ()
		:log_helper(nullptr),
		data_provider_factory(nullptr)
		{
		}

		AssimpMeshDataLoaderPlugin::~AssimpMeshDataLoaderPlugin ()
		{
		}

		bool AssimpMeshDataLoaderPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) throw ( Core::PluginError )
		{
		  
			boost::optional<const std::string&> log_level_name = desc.creation_options.get_optional<std::string>("log_level");
			if(log_level_name.is_initialized())
			{
				log_helper = new Core::LogHelper(getName(), Core::LogHelper::parseLogLevel(log_level_name.get()), plugins_manager->getEngineContext());
			}
		  
			LOG_INFO(log_helper, "Logger initialized");
			
			LOG_INFO(log_helper, "Installing Assimp mesh data loader plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool AssimpMeshDataLoaderPlugin::init () throw ( Core::PluginError )
		{
			
			LOG_INFO(log_helper, "Initializing Assimp mesh data loader plugin")

			LOG_INFO(log_helper, "Creating Assimp mesh data provider factory");
			data_provider_factory = new AssimpMeshDataProvidersFactory(log_helper, engine_context);
			
			LOG_INFO(log_helper, "Registering mesh data provider factory");
			engine_context->getResourceManager()->addDataProviderFactory(data_provider_factory);
			
			return true;
		}

		bool AssimpMeshDataLoaderPlugin::shutdown () throw ( Core::PluginError )
		{
			LOG_INFO(log_helper, "Shutting down Assimp mesh data loader plugin");
		  
			LOG_INFO(log_helper, "Unregistering mesh data provider factory");
			engine_context->getResourceManager()->removeDataProviderFactory(data_provider_factory);
			
			LOG_INFO(log_helper, "Destroying Assimp mesh data provider factory");
			if(data_provider_factory) delete data_provider_factory;
			
			return true;
		}

		bool AssimpMeshDataLoaderPlugin::uninstall () throw ( Core::PluginError )
		{
			LOG_INFO(log_helper, "Uninstalling Assimp mesh data loader plugin");
		  
			if(log_helper) delete log_helper;
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
