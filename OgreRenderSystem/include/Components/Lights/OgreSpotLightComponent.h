#pragma once
#include <Components/Lights/BaseOgreLightComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		static const Core::ComponentType OGRE_SPOT_LIGHT_COMPONENT_TYPE = "Graphics.Light.Spot";
		
		class OgreSpotLightComponent : public BaseOgreLightComponent
		{
			public:
				
				UNKNOWNENGINE_ALIGNED_STRUCT(16) Descriptor
				{
					OgreLightSettings light_settings;
					
					Core::Transform initial_transform;
					Core::LogMessage::Severity log_level;
					
					boost::optional<Math::Vector3> initial_look_at;
					boost::optional<Math::Vector3> initial_direction;
					
					boost::optional<Math::Scalar> inner_angle;
					boost::optional<Math::Scalar> outer_angle;
					boost::optional<Math::Scalar> falloff;
					
					UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
					
					Descriptor():
					log_level(Core::LogMessage::LOG_SEVERITY_NONE)
					{}
				};
				
				OgreSpotLightComponent ( const std::string& name, const Descriptor& desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );
				virtual ~OgreSpotLightComponent();
				virtual Core::ComponentType getType();
				virtual void init ( const Core::Entity* parent_entity );
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
				
			private:
				Descriptor desc;
			
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreSpotLightComponent::Descriptor);