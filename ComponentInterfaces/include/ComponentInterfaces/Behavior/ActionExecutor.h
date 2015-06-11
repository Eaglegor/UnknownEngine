#pragma once

#include <ComponentSystem/IComponentInterface.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ActionExecutor : public Core::IComponentInterface
		{
			public:
				constexpr static const char* getType(){return "ActionExecutor";}
				
				virtual void execute() = 0;
		};
	}
}