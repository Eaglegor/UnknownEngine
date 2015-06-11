#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/RenderSystem/Common/IRenderWindowEventsListener.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class IRenderWindowComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType()
				{
					return "IRenderWindowComponent";
				}

				virtual void addListener(IRenderWindowEventsListener* listener) = 0;
				virtual void removeListener(IRenderWindowEventsListener* listener) = 0;
		};
	}
}