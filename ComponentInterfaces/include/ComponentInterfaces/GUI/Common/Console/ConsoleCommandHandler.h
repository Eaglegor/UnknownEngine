#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/GUI/Common/Console/ConsoleOutputStream.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ConsoleCommandHandler : public Core::IComponentInterface
		{
		public:
			constexpr static const char* getType(){return "ConsoleCommandHandler";}
			
			virtual void onConsoleCommand(const char* command, ConsoleOutputStream& ostream) = 0;
		};
	}
}
