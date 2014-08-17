#pragma once

#include <DataProviders/OgreMeshPtrProvider.h>
#include <DataProvider/DataProviderType.h>
#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
	namespace Core
	{

		class LogHelper;
		class EngineContext;
	}

	namespace Graphics
	{

		class OgreRenderSubsystem;

		const Loader::DataProviderType OGRE_MESH_PTR_FROM_MESH_DATA_PROVIDER_TYPE = "Loader.OgreMeshPtr.OgreMeshPtrFromMeshDataProvider";
		
		class OgreMeshPtrFromMeshDataProvider : public OgreMeshPtrProvider
		{
			public:

				struct Descriptor
				{
					Loader::IDataProvider* mesh_data_provider;
					
					Core::LogMessage::Severity log_level;
					
					Descriptor():
					mesh_data_provider(nullptr),
					log_level(Core::LogMessage::Severity::LOG_SEVERITY_NONE)
					{}
				};

				OgreMeshPtrFromMeshDataProvider ( const std::string &name, const Descriptor &descriptor, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );
				
				virtual const Loader::DataProviderType& getType() override;
				
			protected:
				virtual void internalLoad ( Loader::ResourceContainer &out_container ) override;
				Loader::IDataProvider* mesh_data_provider;
				OgreRenderSubsystem* render_subsystem;
				std::unique_ptr<Core::LogHelper> log_helper;
				bool loaded;
				Loader::ResourceContainer cont;
		};

	} // namespace Graphics
} // namespace UnknownEngine
