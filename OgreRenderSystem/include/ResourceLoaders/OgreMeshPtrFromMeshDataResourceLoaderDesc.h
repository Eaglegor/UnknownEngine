#pragma once

#include <ResourceTypes/Meshes/MeshDataResourceTypeDefinition.h>
#include <ResourceManager/ResourceHandlePtr.h>

namespace UnknownEngine
{
	namespace ResourceLoaders
	{
		struct OgreMeshPtrFromMeshDataResourceLoaderDesc
		{
			Resources::ResourceHandlePtr<Utils::MeshData*> mesh_data;
		};
	}
}
