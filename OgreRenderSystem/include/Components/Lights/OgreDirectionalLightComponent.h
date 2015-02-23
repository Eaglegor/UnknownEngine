#pragma once
#include <Components/Lights/BaseOgreLightComponent.h>
#include <Descriptors/Components/Lights/OgreDirectionalLightComponentDescriptor.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		static const Core::ComponentType OGRE_DIRECTIONAL_LIGHT_COMPONENT_TYPE = "Graphics.Light.Directional";
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) OgreDirectionalLightComponent : public BaseOgreLightComponent
		{
			public:
				
				constexpr static const char* getTypeName(){return "Ogre.DirectionalLight";}
				
				OgreDirectionalLightComponent ( const std::string& name, const OgreDirectionalLightComponentDescriptor& desc, OgreRenderSubsystem* render_subsystem);
				virtual ~OgreDirectionalLightComponent();
				
				virtual Core::ComponentType getType() const override;
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
				
			protected:
				virtual void internalInit (const Core::IEntity* parent_entity) override;
				
			private:
				OgreDirectionalLightComponentDescriptor desc;
				Core::LogHelper logger;
		};
	}
}

