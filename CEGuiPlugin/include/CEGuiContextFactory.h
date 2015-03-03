#pragma once

#include <ComponentSystem/BaseComponentFactory.h>

namespace UnknownEngine
{
	namespace GUI
	{
		class CEGuiContextFactory : public Core::BaseComponentFactory
		{
		public:
			CEGuiContextFactory();
			
			virtual const char* getName() const
			{
				return "CEGui.ContextFactory";
			}
			
		private:
			Core::IComponent* createOgreContext(const Core::ComponentDesc& desc);
		};
	}
}