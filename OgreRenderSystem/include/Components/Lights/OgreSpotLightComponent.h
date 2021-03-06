#pragma once
#include <Components/Lights/BaseOgreLightComponent.h>
#include <Descriptors/Components/Lights/OgreSpotLightComponentDescriptor.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		UNKNOWNENGINE_ALIGNED_CLASS(16) OgreSpotLightComponent : public BaseOgreLightComponent
		{
			public:
				
				constexpr static const char* getTypeName(){return "Ogre.SpotLight";}
				
				OgreSpotLightComponent ( const std::string& name, const OgreSpotLightComponentDescriptor& desc, OgreRenderSubsystem* render_subsystem);
				virtual ~OgreSpotLightComponent();
				
				virtual Core::ComponentType getType() const override {return getTypeName();}
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			protected:
				virtual void internalInit () override;
				
			private:
				OgreSpotLightComponentDescriptor desc;
				Core::LogHelper logger;
			
		};
	}
}

