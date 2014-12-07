#pragma once

#include <DataProviders/OgreMeshPtrProvider.h>
#include <ResourceManager/DataProviders/DataProviderType.h>
#include <Descriptors/DataProviders/OgreMeshPtrFromMeshDataProviderDescriptor.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class ILogger;
	}

	namespace Graphics
	{

		class OgreRenderSubsystem;
		
		const Core::DataProviderType OGRE_MESH_PTR_FROM_MESH_DATA_PROVIDER_TYPE = "Loader.OgreMeshPtr.OgreMeshPtrFromMeshDataProvider";
		
		class OgreMeshPtrFromMeshDataProvider : public OgreMeshPtrProvider
		{
			public:
				OgreMeshPtrFromMeshDataProvider ( const std::string &name, const OgreMeshPtrFromMeshDataProviderDescriptor &descriptor, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );
				virtual ~OgreMeshPtrFromMeshDataProvider();
				
				virtual const Core::DataProviderType getType() const override;
				
			protected:
				virtual void internalLoad ( Core::ResourceContainer &out_container ) override;
				Core::IDataProvider* mesh_data_provider;
				OgreRenderSubsystem* render_subsystem;
				Core::ILogger* logger;
				bool loaded;
				Core::ResourceContainer cont;
		};

	} // namespace Graphics
} // namespace UnknownEngine
