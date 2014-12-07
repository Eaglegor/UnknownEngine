#pragma once
#include <Components/Lights/BaseOgreLightComponent.h>
#include <Descriptors/Components/Lights/OgreSpotLightComponentDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		static const Core::ComponentType OGRE_SPOT_LIGHT_COMPONENT_TYPE = "Graphics.Light.Spot";
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) OgreSpotLightComponent : public BaseOgreLightComponent
		{
			public:
				OgreSpotLightComponent ( const std::string& name, const OgreSpotLightComponentDescriptor& desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );
				virtual ~OgreSpotLightComponent();
				
				virtual Core::ComponentType getType() const override;
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			protected:
				virtual void internalInit (const Core::IEntity* parent_entity) override;
				
			private:
				OgreSpotLightComponentDescriptor desc;
			
		};
	}
}

