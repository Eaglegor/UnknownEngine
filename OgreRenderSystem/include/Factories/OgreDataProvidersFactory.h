#pragma once

#include <ResourceManager/DataProviders/BaseDataProviderFactory.h>

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

		class OgreDataProvidersFactory : public Core::BaseDataProviderFactory
		{
		public:
			OgreDataProvidersFactory();
			virtual const char* getName() const override;
			
			void setRenderSubsystem(OgreRenderSubsystem* render_subsystem);
			
		private:
			Core::IDataProvider* createOgreMeshPtrFromMeshDataProvider ( const Core::DataProviderDesc& desc );
			
			OgreRenderSubsystem* render_subsystem;
			
		};
	}
}