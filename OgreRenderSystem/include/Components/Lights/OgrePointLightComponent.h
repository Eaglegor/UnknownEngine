#pragma once
#include <Components/Lights/BaseOgreLightComponent.h>
#include <Descriptors/Components/Lights/OgrePointLightComponentDescriptor.h>
#include <LogHelper.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		UNKNOWNENGINE_ALIGNED_CLASS(16) OgrePointLightComponent : public BaseOgreLightComponent
		{
			public:
				
				constexpr static const char* getTypeName(){return "Ogre.PointLight";}
				
				OgrePointLightComponent ( const std::string& name, const OgrePointLightComponentDescriptor& desc, OgreRenderSubsystem* render_subsystem );
				virtual ~OgrePointLightComponent();
				
				virtual Core::ComponentType getType() const override {return getTypeName();}
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
				
			protected:
				virtual void internalInit (const Core::IEntity* parent_entity) override;
				
			private:
				OgrePointLightComponentDescriptor desc;
				Core::LogHelper logger;
		};
	}
}

