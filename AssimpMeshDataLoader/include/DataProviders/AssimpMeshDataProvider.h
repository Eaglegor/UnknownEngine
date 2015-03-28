#pragma once

#include <ResourceManager/DataProviders/SeparateLoaderThreadDataProvider.h>
#include <Exception.h>
#include <LogSeverity.h>
#include <LogHelper.h>
#include <DataProviders/AssimpMeshDataProviderDesc.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class ILogger;
	}

	namespace Loader
	{

		static const Core::DataProviderType ASSIMP_MESH_DATA_PROVIDER_TYPE_NAME = "Loader.MeshData.AssimpMeshDataLoader";
		
		class AssimpMeshDataProvider :  public Core::SeparateLoaderThreadDataProvider
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(AssimpMeshDataLoadError);
			
			AssimpMeshDataProvider ( const std::string& name, const AssimpMeshDataProviderDesc &desc, Core::EngineContext* engine_context );
			~AssimpMeshDataProvider();
			
			virtual const Core::DataProviderType getType() const override;
			virtual void internalLoad ( Core::ResourceContainer& out_container ) override;

		private:
			AssimpMeshDataProviderDesc desc;
			Core::LogHelper logger;
		};
		
	}
}