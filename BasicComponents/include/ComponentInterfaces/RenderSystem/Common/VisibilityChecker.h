#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/RenderSystem/Common/VisibilityCheckerListener.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class VisibilityChecker : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "VisibilityChecker";}
				
				virtual bool isVisible() = 0;
				
				virtual void addListener(VisibilityCheckerListener* listener) = 0;
				virtual void removeListener(VisibilityCheckerListener* listener) = 0;
		};
	}
}