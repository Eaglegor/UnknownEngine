#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <Controllers/IESController.h>
#include <Controllers/ESControllersFactory.h>
#include <Descriptors/ESHardwareControllerComponentDesc.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		class ESHardwareControllerComponent : public Core::BaseComponent
		{
		public:
			ESHardwareControllerComponent(const char* name, const ESHardwareControllerComponentDesc& desc, ESControllersFactory *controllers_factory);
			
			virtual void init ();
			virtual void shutdown();
			
			virtual Core::ComponentType getType() const;
			constexpr static const char* getTypeName(){return "Endoscopy.HardwareController";}
			
		private:
			IESController* controller;
			ESHardwareControllerComponentDesc desc;
			ESControllersFactory* controllers_factory;
		};
	}
}