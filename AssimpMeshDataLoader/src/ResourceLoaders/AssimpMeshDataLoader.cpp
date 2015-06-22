#include <ResourceLoaders/AssimpMeshDataLoader.h>

namespace UnknownEngine
{
	namespace ResourceLoaders
	{

		AssimpMeshDataLoader::AssimpMeshDataLoader(const AssimpMeshDataLoaderDesc &desc):
		desc(desc)
		{
		}

		Utils::MeshData *AssimpMeshDataLoader::loadImpl(Utils::MeshData** out_data, size_t &out_data_size, Core::LogHelper &logger)
		{
			*out_data = new Utils::MeshData();
			Utils::MeshData &mesh_data = *(*out_data);

			LOG_INFO(logger, "Started loading file " + desc.filename);

			Assimp::Importer importer;

			unsigned int flags = 0;

			if(desc.postprocessing.flip_texture_coordinates)
			{
				LOG_INFO(logger, "Turning on postprocessor: Flip texture coordinates");
				flags |= aiProcess_FlipUVs;
			}

			if(desc.postprocessing.triangulate)
			{
				LOG_INFO(logger, "Turning on postprocessor: Triangulate");
				flags |= aiProcess_Triangulate;
			}

			if(desc.postprocessing.generate_normals)
			{
				LOG_INFO(logger, "Turning on postprocessor: Generate normals");
				flags |= aiProcess_GenSmoothNormals;
			}

			if(desc.postprocessing.generate_tangents)
			{
				LOG_INFO(logger, "Turning on postprocessor: Generate tangents");
				flags |= aiProcess_CalcTangentSpace;
			}

			LOG_INFO(logger, "Reading file");

			const aiScene* scene = importer.ReadFile(desc.filename.c_str(), flags);
			if(scene == nullptr || !scene->HasMeshes())
			{
				LOG_ERROR(logger, "Error while loading file " + desc.filename);
				delete *out_data;
				*out_data = nullptr;
				return;
			}

			LOG_INFO(logger, "Converting to shared mesh data format");

			aiMesh* first_mesh = scene->mMeshes[0];

			aiVector3D* vertices = first_mesh->mVertices;
			aiVector3D* normals = first_mesh->mNormals;
			aiVector3D* tangents = first_mesh->mTangents;
			aiVector3D* bitangents = first_mesh->mBitangents;

			aiVector3D* texture_coordinates;
			if(first_mesh->HasTextureCoords(0)) texture_coordinates = first_mesh->mTextureCoords[0];

			for(size_t i = 0; i < first_mesh->mNumVertices; ++i)
			{
				if(isInterrupted())
				{
					delete *out_data;
					*out_data = nullptr;
					return;
				}

				Utils::VertexType vertex;
				vertex.setPosition( convertAssimpVector (vertices[i]) );

				if(first_mesh->HasNormals())
				{
					vertex.setNormal( convertAssimpVector (normals[i]) );
				}

				if(first_mesh->HasTangentsAndBitangents())
				{
					vertex.setTangent( convertAssimpVector (tangents[i]) );
					vertex.setBinormal( convertAssimpVector (bitangents[i]) );
				}

				if(first_mesh->HasTextureCoords(0))
				{
					vertex.setTextureCoordinate( convertAssimpTexCoord (texture_coordinates[i]) );
				}

				mesh_data.getVertices().push_back(vertex);
			}

			for(size_t i = 0; i < first_mesh->mNumFaces; ++i)
			{
				if(isInterrupted())
				{
					delete *out_data;
					*out_data = nullptr;
					return;
				}
				for(size_t j = 0; j < first_mesh->mFaces[i].mNumIndices; ++j)
				{
					mesh_data.getIndices().push_back(first_mesh->mFaces[i].mIndices[j]);
				}
			}

			LOG_INFO(logger, "Loading finished");
		}

		void AssimpMeshDataLoader::unloadImpl(Utils::MeshData **data, Core::LogHelper &logger)
		{
			LOG_INFO(logger, "Destroying mesh data");
			delete *data;
			*data = nullptr;
			LOG_INFO(logger, "Mesh data destroyed");
		}

	}
}
