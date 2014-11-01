#pragma once

/*
 * DirectX10RenderSystemPlugin.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <InlineSpecification.h>
#include <Plugins/Plugin.h>
#include <SubsystemDesc.h>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
	}

	namespace Utils
	{
		class LogHelper;
	}
	
	namespace Loader
	{

		class AssimpMeshDataProvidersFactory;

		class AssimpMeshDataLoaderPlugin: public Core::Plugin
		{
			public:
				AssimpMeshDataLoaderPlugin();
				virtual ~AssimpMeshDataLoaderPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				std::unique_ptr<Utils::LogHelper> log_helper;
				std::unique_ptr<AssimpMeshDataProvidersFactory> data_provider_factory;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
