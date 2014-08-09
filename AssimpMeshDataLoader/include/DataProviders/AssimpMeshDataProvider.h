#pragma once
#include <DataProvider/SeparateLoaderThreadDataProvider.h>
#include <Exception.h>

namespace UnknownEngine
{
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
			};
			
			AssimpMeshDataProvider ( const std::string& name, const Descriptor &desc );
			
			virtual const DataProviderType& getType();
			virtual void internalLoad ( ResourceContainer& out_container );

			
			
		private:
			Descriptor desc;
		};
		
	}
}