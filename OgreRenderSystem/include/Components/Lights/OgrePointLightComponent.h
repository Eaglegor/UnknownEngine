#pragma once
#include <Components/Lights/BaseOgreLightComponent.h>
#include <Descriptors/Components/Lights/OgrePointLightComponentDescriptor.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		static const Core::ComponentType OGRE_POINT_LIGHT_COMPONENT_TYPE = "Graphics.Light.Point";
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) OgrePointLightComponent : public BaseOgreLightComponent
		{
			public:
				
				OgrePointLightComponent ( const std::string& name, const OgrePointLightComponentDescriptor& desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );
				virtual ~OgrePointLightComponent();
				
				virtual Core::ComponentType getType() const override;
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
				
			protected:
				virtual void internalInit (const Core::IEntity* parent_entity) override;
				
			private:
				OgrePointLightComponentDescriptor desc;
			
		};
	}
}

