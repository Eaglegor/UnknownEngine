#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <DataProviders/AssimpMeshDataProvider.h>
#include <Mesh/MeshData.h>

namespace UnknownEngine
{
	namespace Loader
	{

		static Math::Vector3 convertAssimpVector(const aiVector3D &vector3)
		{
			return Math::Vector3(vector3.x, vector3.y, vector3.z);
		}
		
		static Utils::TextureCoordinateType convertAssimpTexCoord(const aiVector3D &vector3)
		{
			return Utils::TextureCoordinateType(vector3.x, vector3.y, vector3.z);
		}
		
		AssimpMeshDataProvider::AssimpMeshDataProvider ( const std::string& name, const AssimpMeshDataProvider::Descriptor& desc ) :
			SeparateLoaderThreadDataProvider ( name ),
			desc ( desc )
		{
		}

		const DataProviderType& AssimpMeshDataProvider::getType()
		{
			return ASSIMP_MESH_DATA_PROVIDER_TYPE_NAME;
		}

		void AssimpMeshDataProvider::internalLoad ( ResourceContainer& out_container )
		{
			Assimp::Importer importer;
			
			unsigned int flags = 0;
			
			if(desc.postprocessing.flip_texture_coordinates) flags |= aiProcess_FlipUVs;
			if(desc.postprocessing.triangulate) flags |= aiProcess_Triangulate;
			if(desc.postprocessing.generate_normals) flags |= aiProcess_GenSmoothNormals;
			if(desc.postprocessing.generate_tangents) flags |= aiProcess_CalcTangentSpace;
			
			const aiScene* scene = importer.ReadFile(desc.filename, flags);
			if(scene == nullptr || !scene->HasMeshes()) throw AssimpMeshDataLoadError("Error while loading mesh data");
			
			aiMesh* first_mesh = scene->mMeshes[0];
			
			aiVector3D* vertices = first_mesh->mVertices;
			aiVector3D* normals = first_mesh->mNormals;
			aiVector3D* tangents = first_mesh->mTangents;
			
			aiVector3D* texture_coordinates;
			if(first_mesh->HasTextureCoords(0)) texture_coordinates = first_mesh->mTextureCoords[0];
			
			Utils::MeshData mesh_data;
			
			for(size_t i = 0; i < first_mesh->mNumVertices; ++i)
			{
				Utils::VertexType vertex;
				vertex.setPosition( convertAssimpVector (vertices[i]) );
				
				if(first_mesh->HasNormals()) vertex.setNormal( convertAssimpVector (normals[i]) );
				if(first_mesh->HasTangentsAndBitangents()) vertex.setTangent( convertAssimpVector (tangents[i]) );
				if(first_mesh->HasTextureCoords(0)) vertex.setTextureCoordinate( convertAssimpTexCoord (texture_coordinates[i]) );
				
				mesh_data.getVertices().push_back(vertex);
			}
			
			for(size_t i = 0; i < first_mesh->mNumFaces; ++i)
			{
				for(size_t j = 0; j < first_mesh->mFaces[i].mNumIndices; ++j)
				{
					mesh_data.getIndices().push_back(first_mesh->mFaces[i].mIndices[j]);
				}
			}
			
			out_container.setData<Utils::MeshData>(std::move(mesh_data));
		}
		
	}
}