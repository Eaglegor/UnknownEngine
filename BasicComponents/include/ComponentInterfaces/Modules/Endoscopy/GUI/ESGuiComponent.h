#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/Modules/Endoscopy/GUI/ESGuiComponentListener.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESGuiComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "ESGuiComponent";}
				
				virtual void setHintText(const char* text) = 0;
				virtual void addOperationLog(const char* text) = 0;
				
				virtual void clearInstruments(int port, const char* instrument_asset_name) = 0;
				virtual void addInstrument(int port, const char* instrument_asset_name) = 0;
				virtual void removeInstrument(int port, const char* instrument_asset_name) = 0;
				
				virtual void addListener(ESGuiComponentListener* listener) = 0;
				virtual void removeListener(ESGuiComponentListener* listener) = 0;
		};
	}
}