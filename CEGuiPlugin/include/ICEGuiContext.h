#pragma once

#include <ICEGuiComponent.h>

namespace UnknownEngine
{
	namespace GUI
	{
		class ICEGuiContext
		{
		public:
			virtual ~ICEGuiContext(){}
			
			virtual void initComponent(ICEGuiComponent* component) = 0;
			virtual void shutdownComponent(ICEGuiComponent* component) = 0;
			virtual void destroyComponent(ICEGuiComponent* component) = 0;
		};
	}
}