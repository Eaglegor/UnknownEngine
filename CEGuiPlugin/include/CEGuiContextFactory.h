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
			Core::IComponent* createSynchronizedOgreContext(const Core::ComponentDesc& desc);
			void destroySynchronizedOgreContext(Core::IComponent* component);
			
			Core::IComponent* createSeparateThreadOgreContext(const Core::ComponentDesc& desc);
			void destroySeparateThreadOgreContext(Core::IComponent* component);
			
			Core::IComponent* createFrameWindow(const Core::ComponentDesc &desc);
			void destroyFrameWindow(Core::IComponent* component);
			
			Core::IComponent* createConsoleWindow(const Core::ComponentDesc &desc);
			void destroyConsoleWindow(Core::IComponent* component);
			
			Core::IComponent* context;
		};
	}
}