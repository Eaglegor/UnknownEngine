#pragma once

#include <ResourceManager/BaseResourceLoader.h>
#include <ResourceTypes/Meshes/OgreMeshTypeDefinition.h>
#include <ResourceLoaders/OgreMeshPtrFromMeshDataResourceLoaderDesc.h>

namespace UnknownEngine
{
	namespace ResourceLoaders
	{
		class OgreMeshPtrFromMeshDataResourceLoader : public Resources::BaseResourceLoader<Ogre::Mesh*>
		{
			public:
				OgreMeshPtrFromMeshDataResourceLoader(const ResourceLoaders::OgreMeshPtrFromMeshDataResourceLoaderDesc &desc);

				constexpr static const char* staticGetType(){return "Ogre.MeshPtrFromMeshDataResourceLoader";}
				virtual Resources::ResourceLoaderType getType(){return staticGetType();}

			private:
				virtual void loadImpl(Ogre::Mesh **out_data, size_t &out_data_size, Core::LogHelper &logger);
				virtual void unloadImpl(Ogre::Mesh **data, Core::LogHelper &logger);

				ResourceLoaders::OgreMeshPtrFromMeshDataResourceLoaderDesc &desc;
		};
	}
}
