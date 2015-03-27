#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/Modules/Endoscopy/Behavior/ESEventsListener.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESGuiInstrumentSelectorComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "ESGuiInstrumentSelectorComponent";}
				
				virtual void clearInstruments(int port, const char* instrument_asset_name) = 0;
				virtual void addInstrument(int port, const char* instrument_asset_name) = 0;
				virtual void removeInstrument(int port, const char* instrument_asset_name) = 0;
				
				virtual void addListener(ESEventsListener* listener) = 0;
				virtual void removeListener(ESEventsListener* listener) = 0;
		};
	}
}