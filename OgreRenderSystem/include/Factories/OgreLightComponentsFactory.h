#pragma once

#include <IComponentFactory.h>
#include <Factories/BaseOgreComponentFactory.h>
#include <OgreRenderSubsystem_fwd.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class LogHelper;
	}

	namespace Graphics
	{

		class OgreSpotLightComponent;

		class OgreDirectionalLightComponent;

		class OgrePointLightComponent;

		class OgreLightComponentsFactory : public BaseOgreComponentFactory
		{
		public:
			OgreLightComponentsFactory(OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper);
			virtual const std::string getName();
			virtual const std::unordered_set< Core::ComponentType >& getSupportedTypes();
			virtual const bool supportsType ( const Core::ComponentType& object_type );

		protected:
			virtual Core::Component* internalCreateObject ( const Core::ComponentDesc& desc );
			virtual void internalDestroyObject ( Core::Component* object );
			
		private:
			OgrePointLightComponent* createPointLightComponent(const Core::ComponentDesc& desc );
			void destroyPointLightComponent( Core::Component* object );
			
			OgreDirectionalLightComponent* createDirectionalLightComponent(const Core::ComponentDesc& desc );
			void destroyDirectionalLightComponent( Core::Component* object );
			
			OgreSpotLightComponent* createSpotLightComponent ( const Core::ComponentDesc &desc );
			void destroySpotLightComponent( Core::Component* object);
		};
	}
}