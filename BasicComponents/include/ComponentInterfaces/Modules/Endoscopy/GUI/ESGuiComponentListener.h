#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESGuiComponentListener : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "ESGuiComponentListener";}

				virtual void onRestart() = 0;
				virtual void onInstrumentChanged(int port, const char* instrument_asset_name) = 0;
		};
	}
}