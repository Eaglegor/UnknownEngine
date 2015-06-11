#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/Modules/Endoscopy/Behavior/ESEventsListener.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESGuiRestartComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "ESGuiRestartComponent";}

				virtual void addListener(ESEventsListener* listener) = 0;
				virtual void removeListener(ESEventsListener* listener) = 0;
		};
	}
}