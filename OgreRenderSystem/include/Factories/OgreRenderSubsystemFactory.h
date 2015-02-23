#pragma once

#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreDataProvidersFactory;

		class OgreRenderSubsystem;

		class OgreComponentsFactory;
		class OgreRenderSubsystemFactory : public Core::BaseComponentFactory
		{
		public:
			OgreRenderSubsystemFactory(OgreComponentsFactory* components_factory, OgreDataProvidersFactory* data_providers_factory);
			virtual const char* getName() const {return "Ogre.RenderSubsystemFactory";}
			
		private:
			
			Core::IComponent* createSingleThreadedOgreRenderSubsystem(const Core::ComponentDesc& desc);
			Core::IComponent* createSeparateThreadOgreRenderSubsystem(const Core::ComponentDesc& desc);
			
			void destroyRenderSubsystem(Core::IComponent* component);
			
			Core::IComponent* createOgreRenderWindow(const Core::ComponentDesc& desc);
			
			OgreRenderSubsystem* render_subsystem;
			OgreComponentsFactory* components_factory;
			OgreDataProvidersFactory* data_providers_factory;
		};
	}
}