#pragma once

#include <ResourceManager/BaseResourceLoader.h>
#include <ResourceTypes/Meshes/MeshDataResourceTypeDefinition.h>

namespace UnknownEngine
{
	namespace ResourceLoaders
	{
		class AssimpMeshDataLoader : public Resources::BaseResourceLoader<Utils::MeshData>
		{
			public:
				virtual Resources::ResourceLoaderType getType();

			private:
				virtual void loadImpl(Utils::MeshData** out_data, size_t &out_data_size);
				virtual void unloadImpl(Utils::MeshData **data);
		};
	}
}
