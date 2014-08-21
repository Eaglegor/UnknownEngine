#include <stdafx.h>

#include <DataProviders/OgreMeshPtrFromMeshDataProvider.h>
#include <OgreRenderSubsystem.h>
#include <Converters/OgreVector3Converter.h>
#include <Mesh/MeshData.h>
#include <OgreManualObject.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <boost/lexical_cast.hpp>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreMeshPtrFromMeshDataProvider::OgreMeshPtrFromMeshDataProvider ( const std::string& name, const OgreMeshPtrFromMeshDataProviderDescriptor& descriptor, UnknownEngine::Graphics::OgreRenderSubsystem* render_subsystem, UnknownEngine::Core::EngineContext* engine_context )
			: OgreMeshPtrProvider ( name ),
			  mesh_data_provider ( descriptor.mesh_data_provider ),
			  render_subsystem(render_subsystem),
			  log_helper(nullptr)
		{
			mesh_data_provider->reserve();
			if(descriptor.log_level > Core::LogMessage::Severity::LOG_SEVERITY_NONE)
			{
				log_helper.reset( new Core::LogHelper(getName(), descriptor.log_level, engine_context) );
			}
		}

		void OgreMeshPtrFromMeshDataProvider::internalLoad ( Loader::ResourceContainer& out_container )
		{
			Ogre::ManualObject* manual_object = render_subsystem->getSceneManager()->createManualObject(getName()+".TempObject");
			
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
			
			Ogre::MeshPtr mesh_ptr = manual_object->convertToMesh(getName() + ".OgreMeshPtr");
			
			mesh_data_provider->release();
			
			out_container.setData<Ogre::MeshPtr>(mesh_ptr);
		}
		
		const Loader::DataProviderType& OgreMeshPtrFromMeshDataProvider::getType()
		{
			return OGRE_MESH_PTR_FROM_MESH_DATA_PROVIDER_TYPE;
		}
		
	} // namespace Graphics
} // namespace UnknownEngine
