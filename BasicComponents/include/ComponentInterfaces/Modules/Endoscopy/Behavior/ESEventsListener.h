#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/Modules/Endoscopy/Behavior/ESEvent.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESEventsListener : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "ESEventsListener";}

				virtual void onESEvent(const ESEvent &evt) = 0;
		};
	}
}