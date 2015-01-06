#pragma once

#include <Components/ESHardwareControllerComponent.h>
#include <Descriptors/ESHardwareControllerComponentDesc.h>
#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		class ESHardwareControllerComponentsFactory : public Core::BaseComponentFactory
		{
		public:
			ESHardwareControllerComponentsFactory(ESControllersFactory* controllers_factory);
			virtual const char* getName() const;
			
		private:
			Core::IComponent* createHardwareControllerComponent(const Core::ComponentDesc &component_desc);
			
			ESControllersFactory* controllers_factory;
		};
	}
}