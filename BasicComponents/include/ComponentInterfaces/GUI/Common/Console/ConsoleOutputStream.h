#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/GUI/Common/Console/ConsoleCommandHandler.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ConsoleOutputStream : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "ConsoleOutputStream";}
			
			virtual ConsoleOutputStream& operator<<(const char* text) = 0;
		};
	}
}
		