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
#include <AssimpMeshDataLoaderDescriptorGetter.h>
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

		bool AssimpMeshDataLoaderPlugin::install ( Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc ) 
		{
		  
			AssimpMeshDataLoaderDescriptorGetter descriptor_getter;
			AssimpMeshDataLoaderDescriptor descriptor = desc.descriptor.apply_visitor(descriptor_getter);
			
			if (descriptor.log_level > Utils::LogSeverity::NONE)
			{ 
				log_helper.reset( new Utils::LogHelper(getName(), descriptor.log_level, plugins_manager->getEngineContext()) );
			}
		  
			LOG_INFO(log_helper, "Logger initialized");
			
			LOG_INFO(log_helper, "Installing Assimp mesh data loader plugin");

			this->desc = desc;
			engine_context = plugins_manager->getEngineContext();

			return true;
		}

		bool AssimpMeshDataLoaderPlugin::init () 
		{
			
			LOG_INFO(log_helper, "Initializing Assimp mesh data loader plugin")

			LOG_INFO(log_helper, "Creating Assimp mesh data provider factory");
			data_provider_factory.reset( new AssimpMeshDataProvidersFactory(log_helper.get(), engine_context) );
			
			LOG_INFO(log_helper, "Registering mesh data provider factory");
			engine_context->getResourceManager()->addDataProviderFactory(data_provider_factory.get());
			
			return true;
		}

		bool AssimpMeshDataLoaderPlugin::shutdown () 
		{
			LOG_INFO(log_helper, "Shutting down Assimp mesh data loader plugin");
		  
			LOG_INFO(log_helper, "Unregistering mesh data provider factory");
			engine_context->getResourceManager()->removeDataProviderFactory(data_provider_factory.get());
			
			LOG_INFO(log_helper, "Destroying Assimp mesh data provider factory");
			data_provider_factory.reset();
			
			return true;
		}

		bool AssimpMeshDataLoaderPlugin::uninstall () 
		{
			LOG_INFO(log_helper, "Uninstalling Assimp mesh data loader plugin");
		  
			log_helper.reset();
			return true;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
