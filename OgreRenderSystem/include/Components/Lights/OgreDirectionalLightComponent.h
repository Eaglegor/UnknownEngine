#pragma once
#include <Components/Lights/BaseOgreLightComponent.h>
#include <Descriptors/Components/Lights/OgreDirectionalLightComponentDescriptor.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		UNKNOWNENGINE_ALIGNED_CLASS(16) OgreDirectionalLightComponent : public BaseOgreLightComponent
		{
			public:
				
				OgreDirectionalLightComponent ( const std::string& name, const OgreDirectionalLightComponentDescriptor& desc, OgreRenderSubsystem* render_subsystem);
				virtual ~OgreDirectionalLightComponent();
				
				constexpr static const char* getTypeName(){return "Ogre.DirectionalLight";}				
				virtual Core::ComponentType getType() const override {return getTypeName();}
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
				
			protected:
				virtual void internalInit () override;
				
			private:
				OgreDirectionalLightComponentDescriptor desc;
				Core::LogHelper logger;
		};
	}
}

