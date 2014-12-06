#pragma once
#include <DataProvider/SeparateLoaderThreadDataProvider.h>
#include <Exception.h>
#include <ExportedMessages/LogMessage.h>
#include <memory>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class ILogger;
	}

	namespace Loader
	{

		static const DataProviderType ASSIMP_MESH_DATA_PROVIDER_TYPE_NAME = "Loader.MeshData.AssimpMeshDataLoader";
		
		class AssimpMeshDataProvider : public SeparateLoaderThreadDataProvider
		{
		public:
			UNKNOWNENGINE_SIMPLE_EXCEPTION(AssimpMeshDataLoadError);
			
			struct Descriptor
			{
				struct PostprocessingDesc
				{
					PostprocessingDesc()
					:generate_tangents(false),
					generate_normals(false),
					triangulate(false),
					flip_texture_coordinates(false)
					{}
					
					bool generate_tangents;
					bool generate_normals;
					bool triangulate;
					bool flip_texture_coordinates;
					
				};
				
				PostprocessingDesc postprocessing;
				std::string filename;
				Utils::LogSeverity log_level;
									
				Descriptor():log_level(Utils::LogSeverity::NONE){};
			};
			
			AssimpMeshDataProvider ( const std::string& name, const Descriptor &desc, Core::EngineContext* engine_context );
			~AssimpMeshDataProvider();
			
			virtual const DataProviderType getType() const override;
			virtual void internalLoad ( ResourceContainer& out_container ) override;

		private:
			Descriptor desc;
			Core::ILogger* logger;
			Core::EngineContext* engine_context;
		};
		
	}
}