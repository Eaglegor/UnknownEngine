#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/Modules/Endoscopy/GUI/ESGuiRestartComponentListener.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESGuiRestartComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "ESGuiRestartComponent";}

				virtual void addListener(ESGuiRestartComponentListener* listener) = 0;
				virtual void removeListener(ESGuiRestartComponentListener* listener) = 0;
		};
	}
}