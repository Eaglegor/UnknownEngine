#pragma once

#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreRenderSubsystem;
		class OgreComponentsFactory : public Core::BaseComponentFactory
		{
		public:
			OgreComponentsFactory();
			
			virtual const char* getName() const {return "Ogre.ComponentsFactory";}
			
			void setRenderSubsystem(OgreRenderSubsystem* render_subsystem);
			
		private:
			OgreRenderSubsystem* render_subsystem;
			
			Core::IComponent* createCameraComponent(const Core::ComponentDesc &desc);
			
			Core::IComponent* createDirectionalLightComponent(const Core::ComponentDesc &desc);
			Core::IComponent* createPointLightComponent(const Core::ComponentDesc &desc);
			Core::IComponent* createSpotLightComponent(const Core::ComponentDesc &desc);
			
			Core::IComponent* createRenderableComponent(const Core::ComponentDesc &desc);

			Core::IComponent* createHOQVisibilityChecker(const Core::ComponentDesc &desc);
			
			void destroyOgreComponent(Core::IComponent* component);
		};
	}
}