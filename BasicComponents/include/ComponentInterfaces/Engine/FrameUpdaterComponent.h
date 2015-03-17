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
				constexpr static const char* getType()
				{
					return "FrameUpdaterComponent";
				}

				virtual void addListener(UpdateFrameListenerComponent* listener) = 0;
				virtual void removeListener(UpdateFrameListenerComponent* listener) = 0;
		};
	}
}
