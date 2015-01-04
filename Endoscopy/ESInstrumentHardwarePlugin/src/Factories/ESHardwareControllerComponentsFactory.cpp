#include <Factories/ESHardwareControllerComponentsFactory.h>
#include <ComponentSystem/ComponentDesc.h>
#include <Components/ESHardwareControllerComponent.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		ESHardwareControllerComponentsFactory::ESHardwareControllerComponentsFactory ( ESControllersFactory* controllers_factory ):
		controllers_factory(controllers_factory)
		{
			CreatableObjectDesc desc;
			desc.type = Core::ComponentType(ESHardwareControllerComponent::getTypeName());
			desc.creator = std::bind(&ESHardwareControllerComponentsFactory::createHardwareControllerComponent, this, std::placeholders::_1);
			registerCreator(desc);
		}

		const char* ESHardwareControllerComponentsFactory::getName() const
		{
			return "Endoscopy.ESInstrumentHardwarePlugin.ESHardwareControllerComponentsFactory";
		}
		
		Core::IComponent* ESHardwareControllerComponentsFactory::createHardwareControllerComponent ( const Core::ComponentDesc& component_desc )
		{
			ESHardwareControllerComponentDesc desc;
			desc.controller_type = ESControllerType::JOYSTICK;
			
			ESHardwareControllerComponent* component = new ESHardwareControllerComponent(component_desc.name.c_str(), desc, controllers_factory);
			
			return component;
		}
	}
}