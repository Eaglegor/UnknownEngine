#include <ResourceLoaders/AssimpMeshDataLoader.h>

namespace UnknownEngine
{
	namespace ResourceLoaders
	{

		Resources::ResourceLoaderType AssimpMeshDataLoader::getType()
		{

		}

		Utils::MeshData *AssimpMeshDataLoader::loadImpl(Utils::MeshData** out_data, size_t &out_data_size)
		{
			Utils::MeshData* mesh_data = new Utils::MeshData();
			out_data =
		}

		void AssimpMeshDataLoader::unloadImpl(Utils::MeshData **data)
		{
			delete data;
		}

	}
}
