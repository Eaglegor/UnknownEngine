#include <ESGUIComponentsFactory.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		ESGUIComponentsFactory::ESGUIComponentsFactory()
		{

		}

		Core::IComponent* ESGUIComponentsFactory::createESHintComponent(const Core::ComponentDesc &desc)
		{
			return nullptr;
		}

		Core::IComponent* ESGUIComponentsFactory::createESRestartButtonComponent(const Core::ComponentDesc &desc)
		{
			return nullptr;
		}

		Core::IComponent* ESGUIComponentsFactory::createESCrosshairComponent(const Core::ComponentDesc &desc)
		{
			return nullptr;
		}

		Core::IComponent* ESGUIComponentsFactory::createESInstrumentChangerComponent(const Core::ComponentDesc &desc)
		{
			return nullptr;
		}

		void destroyESGUIComponent(Core::IComponent* component)
		{

		}
	}
}