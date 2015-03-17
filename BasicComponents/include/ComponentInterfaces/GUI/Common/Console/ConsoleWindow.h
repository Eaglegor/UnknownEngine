#pragma once

#include <ComponentSystem/IComponentInterface.h>
#include <ComponentInterfaces/GUI/Common/Console/ConsoleCommandHandler.h>
#include <ComponentInterfaces/GUI/Common/Console/ConsoleOutputStream.h>

namespace UnknownEngine
{
	namespace ComponentInterfaces
	{
		class ConsoleWindow : public Core::IComponentInterface
		{
			constexpr static const char* getType(){return "ConsoleWindow";}
			
			virtual void addCommandHandler(const char* command, ConsoleCommandHandler* handler) = 0;
			virtual void removeCommandHandler(const char* command, ConsoleCommandHandler* handler) = 0;
			
			virtual ConsoleOutputStream& getOutputStream() = 0;
		};
	}
}
		