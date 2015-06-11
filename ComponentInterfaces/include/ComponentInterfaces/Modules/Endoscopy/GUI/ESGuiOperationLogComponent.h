#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/Modules/Endoscopy/GUI/ESGuiComponentListener.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ESGuiOperationLogComponent : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "ESGuiOperationLogComponent";}
				
				virtual void addOperationLog(const char* text) = 0;
		};
	}
}