#include <Components/ESHardwareControllerComponent.h>
#include <assert.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		ESHardwareControllerComponent::ESHardwareControllerComponent ( const char* name, const ESHardwareControllerComponentDesc &desc, ESControllersFactory* controllers_factory ):
		BaseComponent ( name ),
		desc(desc),
		controllers_factory(controllers_factory),
		controller(nullptr)
		{
		}
		
		bool ESHardwareControllerComponent::init ()
		{
			assert(controllers_factory != nullptr);
			
			controller = controllers_factory->createController(getName(), desc.controller_type);
			
			if(!controller) return false;

			controller->init();
			
			return true;
		}

		void ESHardwareControllerComponent::shutdown()
		{
			assert(controllers_factory != nullptr);
			
			controller->shutdown();
			controllers_factory->destroyController(controller);
		}
		
		Core::ComponentType ESHardwareControllerComponent::getType() const
		{
			return Core::ComponentType(getTypeName());
		}

		Core::IComponentInterface* ESHardwareControllerComponent::getInterface ( const Core::ComponentType& type )
		{
			using namespace ComponentInterfaces;
			if(controller && type == ESHardwareStateNotifier::getTypeName()) return static_cast<ESHardwareStateNotifier*>(controller);
			return nullptr;
		}

	}
}