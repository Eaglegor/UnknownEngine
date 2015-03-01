#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class FrameUpdaterComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getTypeName()
				{
					return "Interface.FrameUpdaterComponent";
				}

				virtual void addListener(UpdateFrameListenerComponent* listener) = 0;
				virtual void removeListener(UpdateFrameListenerComponent* listener) = 0;
		};
	}
}
