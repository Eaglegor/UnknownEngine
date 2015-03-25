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
			void destroyESHintComponent(Core::IComponent* component);
			
			Core::IComponent* createESRestartButtonComponent(const Core::ComponentDesc &desc);
			void destroyESRestartButtonComponent(Core::IComponent* component);
			
			Core::IComponent* createESCrosshairComponent(const Core::ComponentDesc &desc);
			void destroyESCrosshairComponent(Core::IComponent* component);
			
			Core::IComponent* createESInstrumentSelectorComponent(const Core::ComponentDesc &desc);
			void destroyESInstrumentSelectorComponent(Core::IComponent* component);
		};
	}
}