#pragma once

#include <ResourceManager/BaseResourceLoader.h>
#include <ResourceTypes/Meshes/MeshDataResourceTypeDefinition.h>
#include <ResourceLoaders/AssimpMeshDataLoaderDesc.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace ResourceLoaders
	{
		class AssimpMeshDataLoader : public Resources::BaseResourceLoader<Utils::MeshData>
		{
			public:
				virtual AssimpMeshDataLoader(const AssimpMeshDataLoaderDesc &desc);

				static constexpr const char* staticGetType(){return "Assimp.MeshDataLoader";}
				virtual Resources::ResourceLoaderType getType(){return staticGetType();}

			private:
				virtual void loadImpl(Utils::MeshData** out_data, size_t &out_data_size, Core::LogHelper &logger);
				virtual void unloadImpl(Utils::MeshData **data, Core::LogHelper &logger);

				AssimpMeshDataLoaderDesc desc;
		};
	}
}
