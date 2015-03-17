#pragma once

#include <ComponentSystem/IComponentInterface.h>


namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class VisibilityCheckerListener : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "VisibilityChecker";}
				
				virtual void onObjectVisible() = 0;
				virtual void onObjectInvisible() = 0;
		};
	}
}