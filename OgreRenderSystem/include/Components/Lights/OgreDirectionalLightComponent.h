#pragma once
#include <Components/Lights/BaseOgreLightComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		static const Core::ComponentType OGRE_DIRECTIONAL_LIGHT_COMPONENT_TYPE = "Graphics.Light.Directional";
		
		class OgreDirectionalLightComponent : public BaseOgreLightComponent
		{
			public:
				
				UNKNOWNENGINE_ALIGNED_STRUCT(16) Descriptor
				{
					OgreLightSettings light_settings;
					
					Core::Transform initial_transform;
					Core::LogMessage::Severity log_level;
					
					boost::optional<Math::Vector3> initial_look_at;
					boost::optional<Math::Vector3> initial_direction;
					
					UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
					
					Descriptor():
					log_level(Core::LogMessage::Severity::LOG_SEVERITY_NONE)
					{}
				};
				
				OgreDirectionalLightComponent ( const std::string& name, const Descriptor& desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );
				virtual ~OgreDirectionalLightComponent();
				virtual Core::ComponentType getType();
				virtual void init ( const Core::Entity* parent_entity );
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
				
			private:
				Descriptor desc;
			
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreDirectionalLightComponent::Descriptor);