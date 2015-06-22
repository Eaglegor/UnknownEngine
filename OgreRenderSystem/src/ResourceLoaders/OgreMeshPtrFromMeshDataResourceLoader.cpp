#include <ResourceLoaders/OgreMeshPtrFromMeshDataResourceLoader.h>

namespace UnknownEngine
{
	namespace ResourceLoaders
	{

		OgreMeshPtrFromMeshDataResourceLoader::OgreMeshPtrFromMeshDataResourceLoader(const OgreMeshPtrFromMeshDataResourceLoaderDesc &desc):
		desc(desc)
		{
		}

		void OgreMeshPtrFromMeshDataResourceLoader::loadImpl(Ogre::Mesh **out_data, size_t &out_data_size, Core::LogHelper &logger)
		{

			Ogre::ManualObject* manual_object = render_subsystem->getSceneManager()->createManualObject();

			manual_object->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);

			for(const Utils::VertexType& vertex : desc.mesh_data->getVertices())
			{
				const Math::Vector3 &position = vertex.getPosition();
				manual_object->position( OgreVector3Converter::toOgreVector(position) );

				if(vertex.hasNormal())
				{
					const Math::Vector3 &normal = vertex.getNormal();
					manual_object->normal( OgreVector3Converter::toOgreVector(normal) );
				}

				if(vertex.hasTangent())
				{
					const Math::Vector3 &tangent = vertex.getTangent();
					manual_object->tangent( OgreVector3Converter::toOgreVector(tangent) );
				}

				if(vertex.hasTextureCoordinate())
				{
					const Utils::TextureCoordinateType &tex_coord = vertex.getTextureCoordinate();
					manual_object->textureCoord( tex_coord.u(), tex_coord.v(), tex_coord.w() );
				}
			}

			for(const Utils::IndexType& index : desc.mesh_data->getIndices())
			{
				manual_object->index(index);
			}

			manual_object->end();

			*out_data = manual_object->convertToMesh(manual_object->getName()).get();

			out_container.setData<Ogre::MeshPtr>(mesh_ptr);

		}

		void OgreMeshPtrFromMeshDataResourceLoader::unloadImpl(Ogre::Mesh **data, Core::LogHelper &logger)
		{

		}

	}
}
