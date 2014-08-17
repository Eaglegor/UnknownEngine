#pragma once
#include <DataProvider/SeparateLoaderThreadDataProvider.h>
#include <Exception.h>
#include <ExportedMessages/LogMessage.h>
#include <memory>

namespace UnknownEngine
{
	namespace Core
	{

		class LogHelper;
		class EngineContext;
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
				Core::LogMessage::Severity log_level;
									
				Descriptor():log_level(Core::LogMessage::Severity::LOG_SEVERITY_NONE){};
			};
			
			AssimpMeshDataProvider ( const std::string& name, const Descriptor &desc, Core::EngineContext* engine_context );
			
			virtual const DataProviderType& getType();
			virtual void internalLoad ( ResourceContainer& out_container );

			
			
		private:
			Descriptor desc;
			std::unique_ptr<Core::LogHelper> log_helper;
			Core::EngineContext* engine_context;
		};
		
	}
}