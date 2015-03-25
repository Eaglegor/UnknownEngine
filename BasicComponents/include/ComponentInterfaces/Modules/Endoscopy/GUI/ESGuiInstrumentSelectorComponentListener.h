#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESGuiInstrumentSelectorComponentListener : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "ESGuiInstrumentSelectorComponentListener";}

				virtual void onInstrumentChanged(int port, const char* instrument_asset_name) = 0;
		};
	}
}