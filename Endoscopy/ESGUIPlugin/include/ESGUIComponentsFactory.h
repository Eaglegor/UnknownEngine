#pragma once

#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace Endoscopy
	{
		class ESGUIComponentsFactory : public Core::BaseComponentFactory
		{
		public:
			ESGUIComponentsFactory();

			virtual const char* getName() const override { return "Endoscopy.ESGUIComponentsFactory"; }

		private:
			Core::IComponent* createESHintComponent(const Core::ComponentDesc &desc);
			Core::IComponent* createESRestartButtonComponent(const Core::ComponentDesc &desc);
			Core::IComponent* createESCrosshairComponent(const Core::ComponentDesc &desc);
			Core::IComponent* createESInstrumentChangerComponent(const Core::ComponentDesc &desc);

			void destroyESGUIComponent(Core::IComponent* component);
		};
	}
}