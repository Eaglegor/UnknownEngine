#pragma once

#include <InlineSpecification.h>
#include <Plugins/BasePlugin.h>
#include <Plugins/SubsystemDesc.h>

namespace UnknownEngine
{

	namespace Core
	{
		struct SubsystemDesc;
		class EngineContext;
		class ILogger;
	}

	namespace Loader
	{

		class AssimpMeshDataProvidersFactory;

		class AssimpMeshDataLoaderPlugin: public Core::BasePlugin
		{
			public:
				AssimpMeshDataLoaderPlugin(const char* name);
				virtual ~AssimpMeshDataLoaderPlugin();

				virtual bool install(Core::PluginsManager* plugins_manager, const Core::SubsystemDesc& desc)  override;
				virtual bool init()  override;
				virtual bool shutdown()  override;
				virtual bool uninstall()  override;

			private:
				Core::SubsystemDesc desc;
				Core::EngineContext* engine_context;
				Core::ILogger* logger;
				std::unique_ptr<AssimpMeshDataProvidersFactory> data_provider_factory;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
