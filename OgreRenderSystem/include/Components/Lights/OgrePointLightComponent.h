#pragma once
#include <Components/Lights/BaseOgreLightComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		static const Core::ComponentType OGRE_POINT_LIGHT_COMPONENT_TYPE = "Graphics.Light.Point";
		
		class OgrePointLightComponent : public BaseOgreLightComponent
		{
			public:
				
				UNKNOWNENGINE_ALIGNED_STRUCT(16) Descriptor
				{
					OgreLightSettings light_settings;
					
					Core::Transform initial_transform;
					Core::LogMessage::Severity log_level;
					
					UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
					
					Descriptor():
					log_level(Core::LogMessage::Severity::LOG_SEVERITY_NONE)
					{}
				};
				
				OgrePointLightComponent ( const std::string& name, const Descriptor& desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );
				virtual ~OgrePointLightComponent();
				virtual Core::ComponentType getType();
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
				
			protected:
				virtual void internalInit (const Core::Entity* parent_entity);
				
			private:
				Descriptor desc;
			
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgrePointLightComponent::Descriptor);