#include <Components/ESHardwareControllerComponent.h>
#include <assert.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		ESHardwareControllerComponent::ESHardwareControllerComponent ( const char* name, const ESHardwareControllerComponentDesc &desc, ESControllersFactory* controllers_factory ):
		BaseComponent ( name ),
		desc(desc),
		controllers_factory(controllers_factory)
		{
		}
		
		void ESHardwareControllerComponent::init ()
		{
			assert(controllers_factory != nullptr);
			
			controller = controllers_factory->createController(getName(), desc.controller_type);
			controller->init();
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


	}
}