#pragma once

#include <IComponentFactory.h>

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

		class OgreRenderSubsystem;

		class OgreLightComponentsFactory : public UnknownEngine::Core::IComponentFactory
		{
		public:
			OgreLightComponentsFactory(OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper);
			virtual Core::Component* createObject ( const Core::ComponentDesc& desc );
			virtual void destroyObject ( Core::Component* object );
			virtual const std::string getName();
			virtual const std::unordered_set< Core::ComponentType >& getSupportedTypes();
			virtual const bool supportsType ( const Core::ComponentType& object_type );
			
		private:
			std::unordered_set<Core::ComponentType> supported_types;

			Core::EngineContext* engine_context;
			OgreRenderSubsystem* render_subsystem;
			Core::LogHelper* log_helper;
			
			OgrePointLightComponent* createPointLightComponent(const Core::ComponentDesc& desc );
			void destroyPointLightComponent( Core::Component* object );
			
			OgreDirectionalLightComponent* createDirectionalLightComponent(const Core::ComponentDesc& desc );
			void destroyDirectionalLightComponent( Core::Component* object );
			
			OgreSpotLightComponent* createSpotLightComponent ( const Core::ComponentDesc &desc );
			void destroySpotLightComponent( Core::Component* object);
		};
	}
}