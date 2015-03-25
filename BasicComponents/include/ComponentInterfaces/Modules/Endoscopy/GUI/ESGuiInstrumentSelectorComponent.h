#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/Modules/Endoscopy/GUI/ESGuiInstrumentSelectorComponentListener.h>

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
				
				virtual void addListener(ESGuiInstrumentSelectorComponentListener* listener) = 0;
				virtual void removeListener(ESGuiInstrumentSelectorComponentListener* listener) = 0;
		};
	}
}