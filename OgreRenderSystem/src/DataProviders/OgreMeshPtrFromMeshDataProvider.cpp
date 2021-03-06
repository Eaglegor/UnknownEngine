#include <stdafx.h>

#include <DataProviders/OgreMeshPtrFromMeshDataProvider.h>
#include <OgreRenderSubsystem.h>
#include <Converters/OgreVector3Converter.h>
#include <Mesh/MeshData.h>
#include <OgreManualObject.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <boost/lexical_cast.hpp>
#include <Logging.h>
#include <ResourceManager/ResourceManager.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreMeshPtrFromMeshDataProvider::OgreMeshPtrFromMeshDataProvider ( const std::string& name, const OgreMeshPtrFromMeshDataProviderDescriptor& descriptor, UnknownEngine::Graphics::OgreRenderSubsystem* render_subsystem )
			: OgreMeshPtrProvider ( name ),
			  mesh_data_provider ( descriptor.mesh_data_provider ),
			  render_subsystem(render_subsystem),
			  logger(nullptr)
		{
			GET_DATA_PROVIDER(mesh_data_provider->getName());
			logger = CREATE_LOGGER(getName(), descriptor.log_level);
		}

		OgreMeshPtrFromMeshDataProvider::~OgreMeshPtrFromMeshDataProvider()
		{
			RELEASE_LOGGER(logger);
		}
		
		void OgreMeshPtrFromMeshDataProvider::internalLoad ( Core::ResourceContainer& out_container )
		{
			Ogre::ManualObject* manual_object = render_subsystem->getSceneManager()->createManualObject(std::string(getName())+".TempObject");
			
			const Utils::MeshData& mesh_data = mesh_data_provider->getResource().getData<Utils::MeshData>();
			
			manual_object->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
			
			for(const Utils::VertexType& vertex : mesh_data.getVertices())
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
			
			for(const Utils::IndexType& index : mesh_data.getIndices())
			{
				manual_object->index(index);
			}
			
			manual_object->end();
			
			Ogre::MeshPtr mesh_ptr = manual_object->convertToMesh(std::string(getName()) + ".OgreMeshPtr");
			
			RELEASE_DATA_PROVIDER(mesh_data_provider);
			
			out_container.setData<Ogre::MeshPtr>(mesh_ptr);
		}
		
		const Core::DataProviderType OgreMeshPtrFromMeshDataProvider::getType() const
		{
			return OGRE_MESH_PTR_FROM_MESH_DATA_PROVIDER_TYPE;
		}
		
	} // namespace Graphics
} // namespace UnknownEngine
