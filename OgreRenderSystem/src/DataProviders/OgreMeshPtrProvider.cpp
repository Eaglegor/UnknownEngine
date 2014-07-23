#include <stdafx.h>

#include <DataProviders/OgreMeshPtrProvider.h>
#include <Mesh/MeshData.h>
#include <OgreManualObject.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>

namespace UnknownEngine {
	namespace Graphics {

		OgreMeshPtrProvider::OgreMeshPtrProvider(const std::string &name, const Descriptor &descriptor)
			: Loader::SeparateLoaderThreadDataProvider(name),
			  mesh_data_provider(descriptor.mesh_data_provider)
		{
		}

		void OgreMeshPtrProvider::internalLoad(Loader::ResourceContainer &out_container)
		{
			const Utils::MeshData& mesh_data = mesh_data_provider->getResource().getData<const Utils::MeshData>();

			Ogre::SceneManager &mgr = *Ogre::Root::getSingleton().getSceneManagerIterator().begin();
			Ogre::ManualObject *manual_object = mgr.createManualObject(getName()+".TemporaryObject");

			for( const Utils::VertexType& vertex : mesh_data.getVertices())
			{
				manual_object.position(vertex.getPosition().x, vertex.getPosition().y(), vertex.getPosition().z());
				if(vertex.hasNormal()) manual_object.normal(vertex.getNormal().x, vertex.getNormal().y(), vertex.getNormal().z());
				if(vertex.hasTangent()) manual_object.tangent(vertex.getTangent().x, vertex.getTangent().y(), vertex.getTangent().z());
				if(vertex.hasTextureCoordinate()) manual_object.textureCoord(vertex.getTextureCoordinate().u(), vertex.getTextureCoordinate().v(), vertex.getTextureCoordinate().w());
			}

			for( const Utils::IndexType& index : mesh_data.getIndices())
			{
				manual_object.index(index);
			}

			MeshPtr mesh = manual_object.convertToMesh(getName()+".Mesh");
			out_container.setData<MeshPtr> mesh;

			mgr.destroyManualObject(manual_object);
		}

	} // namespace Graphics
} // namespace UnknownEngine
